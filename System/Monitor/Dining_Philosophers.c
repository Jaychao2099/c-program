#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define N 5 // 哲學家數量
volatile sig_atomic_t terminate = 0; // 全域終止標誌

typedef struct monitor monitor_t;
typedef enum {thinking, hungry, eating} state_t;

struct monitor{
    state_t *state;
    pthread_cond_t *self;
    pthread_mutex_t mutex;  // cv 用的 mutex
    void (*pickup)(int);
    void (*putdown)(int);
    void (*test)(int);
    void (*output)(int);
    int eating_count[N];    // 計數器陣列
};

monitor_t monitor;

void test(int i){        // try to eat
    //No neighbors are eating and Pi is hungry
    if ((monitor.state[(i+N-1)%N] != eating) && 
        (monitor.state[(i+1)%N] != eating) && 
        (monitor.state[i] == hungry)){
        monitor.state[i] = eating;
        pthread_cond_signal(&monitor.self[i]);
    }
}

void pickup(int i){     // pickup chopsticks
    pthread_mutex_lock(&monitor.mutex);
    monitor.state[i] = hungry;
    monitor.test(i);    //try to eat
    if (monitor.state[i] != eating){
        pthread_cond_wait(&monitor.self[i], &monitor.mutex);
    }
    pthread_mutex_unlock(&monitor.mutex);
}

void putdown(int i){
    pthread_mutex_lock(&monitor.mutex);
    monitor.state[i] = thinking;
    monitor.test((i+N-1)%N);        // check if neighbors are waiting to eat
    monitor.test((i+1)%N);
    pthread_mutex_unlock(&monitor.mutex);
}

void output(int now){      // 顯示每個哲學家的吃飯次數
    printf("[");
    for (int i = 0; i < N; i++){
        printf("%d ", monitor.eating_count[i]);
    }
    printf("] now: %d\n", now);
}

void *philosopher(void *arg){
    int i = *(int *)arg;
    while(!terminate){
        sleep(1);    // 模擬思考時間
        monitor.pickup(i);
        // -----------
        // 檢查是否在 pickup 後收到終止信號
        if (terminate) {
            monitor.putdown(i); // 如果收到信號，放下叉子並退出
            break;
        }
        pthread_mutex_lock(&monitor.mutex);
        monitor.eating_count[i]++;  // 更新計數器
        monitor.output(i);          // 顯示計數器
        pthread_mutex_unlock(&monitor.mutex);
        // -----------
        sleep(1);   // 模擬吃飯時間
        monitor.putdown(i);     // Put down chopsticks
    }
}

void init_monitor(){
    monitor.state = malloc(N * sizeof(state_t));
    monitor.self = malloc(N * sizeof(pthread_cond_t));
    for (int i = 0; i < N; i++){
        monitor.state[i] = thinking;
        pthread_cond_init(&monitor.self[i], NULL);
        monitor.eating_count[i] = 0;
    }
    pthread_mutex_init(&monitor.mutex, NULL);   // 初始化 mutex
    monitor.pickup = pickup;
    monitor.putdown = putdown;
    monitor.test = test;
    monitor.output = output;
}

static void cleanup(){     // 釋放資源
    for (int i = 0; i < N; i++){
        pthread_cond_destroy(&monitor.self[i]);
    }
    pthread_mutex_destroy(&monitor.mutex);
    free(monitor.state);
    free(monitor.self);
}

void handler(){     // Ctrl+C 時釋放資源
    printf("\nCtrl+C pressed, exiting...\n");
    terminate = 1; // 設置終止標誌
}

int main(){
    signal(SIGINT, handler);    // 設定 Ctrl+C 的 handler
    int e = atexit(cleanup);    // 結束時釋放資源
    if (e != 0) {
        fprintf(stderr, "cannot set exit function\n");
        exit(EXIT_FAILURE);
    }

    pthread_t philosophers[N];  // 哲學家執行緒
    int id[N];  // 哲學家編號
    
    init_monitor();     // 初始化 monitor

    for (int i = 0; i < N; i++){
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&id[i]);
    }
    for (int i = 0; i < N; i++){
        pthread_join(philosophers[i], NULL);
    }
    return 0;
}