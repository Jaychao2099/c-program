#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // 哲學家數量

/* 狀態枚舉 */
typedef enum {thinking, hungry, eating} state_t;

/* forward declaration */
typedef struct monitor Monitor_t;
typedef void (*func_t)(Monitor_t *, int);

/* Monitor 物件結構定義 */
struct monitor {
    state_t *state;               // 各哲學家狀態
    pthread_cond_t *self;         // 條件變數
    pthread_mutex_t mutex;        // cv 用的 mutex
    int eating_count[N];          // 計數器陣列

    func_t pickup, putdown, test, output; // 方法
};

/* 哲學家 參數 */
typedef struct params {
    int id;
    Monitor_t *monitor;
} params_t;

/* 方法實作 */
static void test_impl(Monitor_t *self, int i) {
    // try to eat
    if ((self->state[(i+N-1)%N] != eating) && 
        (self->state[(i+1)%N] != eating) && 
        (self->state[i] == hungry)) {
        self->state[i] = eating;
        pthread_cond_signal(&self->self[i]);
    }
}

static void pickup_impl(Monitor_t *self, int i) {
    // pickup chopsticks
    self->state[i] = hungry;
    self->test(self, i);    // try to eat
    if (self->state[i] != eating) {
        pthread_cond_wait(&self->self[i], &self->mutex);
    }
}

static void putdown_impl(Monitor_t *self, int i) {
    self->state[i] = thinking;
    self->test(self, (i+N-1)%N);  // check if left neighbor is waiting to eat
    self->test(self, (i+1)%N);    // check if right neighbor is waiting to eat
}

static void output_impl(Monitor_t *self, int now) {
    // 顯示每個哲學家的吃飯次數
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d ", self->eating_count[i]);
    }
    printf("] now: %d\n", now);
}

/* 哲學家執行緒函數 */
void *philosopher(void *arg) {
    // 取得參數
    int i = ((params_t *)arg)->id;
    Monitor_t *monitor = ((params_t *)arg)->monitor;
    
    while(1) {
        pthread_mutex_lock(&monitor->mutex);
        monitor->pickup(monitor, i);
        monitor->eating_count[i]++;        // 更新計數器
        monitor->output(monitor, i);       // 顯示計數器
        pthread_mutex_unlock(&monitor->mutex);
        
        sleep(1);  // 吃飯時間
        
        pthread_mutex_lock(&monitor->mutex);
        monitor->putdown(monitor, i);      // 放下筷子
        pthread_mutex_unlock(&monitor->mutex);
        
        sleep(1);  // 思考時間
    }
    
    return NULL;
}

/* Monitor 初始化函數 */
int init_monitor(Monitor_t **monitor) {
    if (NULL == (*monitor = malloc(sizeof(Monitor_t)))) return -1;

    // 為狀態和條件變數分配記憶體
    (*monitor)->state = malloc(N * sizeof(state_t));
    (*monitor)->self = malloc(N * sizeof(pthread_cond_t));
    
    // 初始化各哲學家狀態和條件變數
    for (int i = 0; i < N; i++) {
        (*monitor)->state[i] = thinking;
        pthread_cond_init(&(*monitor)->self[i], NULL);
        (*monitor)->eating_count[i] = 0;
    }
    
    // 初始化互斥鎖
    pthread_mutex_init(&(*monitor)->mutex, NULL);
    
    // 設定方法指標
    (*monitor)->pickup = pickup_impl;
    (*monitor)->putdown = putdown_impl;
    (*monitor)->test = test_impl;
    (*monitor)->output = output_impl;
    
    return 0;
}

/* 釋放 Monitor 資源 */
void cleanup_monitor(Monitor_t *monitor) {
    if (monitor == NULL) return;
    
    for (int i = 0; i < N; i++) {
        pthread_cond_destroy(&monitor->self[i]);
    }
    pthread_mutex_destroy(&monitor->mutex);
    
    free(monitor->state);
    free(monitor->self);
    free(monitor);
}

int main(int argc, char *argv[]) {
    pthread_t philosophers[N];            // 哲學家執行緒
    params_t *params[N];                       // 參數陣列
    Monitor_t *monitor = NULL;
    
    // 初始化 Monitor 物件
    if (init_monitor(&monitor) != 0) {
        fprintf(stderr, "Failed to initialize monitor\n");
        return -1;
    }
    
    // 建立哲學家執行緒
    for (int i = 0; i < N; i++) {
        params[i] = malloc(sizeof(params_t));
        params[i]->id = i;                  // 哲學家編號
        params[i]->monitor = monitor;      // Monitor 物件指標
        
        pthread_create(&philosophers[i], NULL, philosopher, (void *)params[i]);
    }
    
    // 等待哲學家執行緒結束 (實際上不會發生)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
        free(params[i]);
    }
    
    // 釋放 Monitor 資源
    cleanup_monitor(monitor);
    
    return 0;
}