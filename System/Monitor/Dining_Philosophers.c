#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // 哲學家數量

typedef struct{
    enum {thinking, hungry, eating} *state;
    pthread_cond_t *self;
    pthread_mutex_t mutex;  // cv 用的 mutex
    void (*pickup)(int);
    void (*putdown)(int);
    void (*test)(int);
    void (*init)();
    void (*output)(int);
    int eating_count[N];    // 計數器陣列
} monitor_t;

monitor_t monitor;

void pickup(int i){     // pickup chopsticks
    monitor.state[i] = hungry;
    monitor.test(i);    //try to eat
    if (monitor.state[i] != eating){
        pthread_cond_wait(&monitor.self[i], &monitor.mutex);
    }
}

void putdown(int i){
    monitor.state[i] = thinking;
    monitor.test((i+N-1)%N);        // check if neighbors are waiting to eat
    monitor.test((i+1)%N);
}

void test(int i){        // try to eat
    //No neighbors are eating and Pi is hungry
    if ((monitor.state[(i+N-1)%N] != eating) && (monitor.state[(i+1)%N] != eating) && (monitor.state[i] == hungry)){
        monitor.state[i] = eating;
        pthread_cond_signal(&monitor.self[i]);
    }
}

void init(){
    monitor.state = malloc(N * sizeof(enum{thinking, hungry, eating}));
    monitor.self = malloc(N * sizeof(sem_t));
    for (int i = 0; i < N; i++){
        monitor.state[i] = thinking;
        pthread_cond_init(&monitor.self[i], NULL);
    }
    pthread_mutex_init(&monitor.mutex, NULL);   // 初始化 mutex
    for (int i = 0; i < N; i++) {
        monitor.eating_count[i] = 0;
    }
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
    while(1){
        sleep(1);
        monitor.pickup(i);
        monitor.eating_count[i]++;  // 更新計數器
        monitor.output(i);          // 顯示計數器
        sleep(1);
        monitor.putdown(i);
    }
}

int main(){
    pthread_t philosophers[N];
    int id[N];
    monitor.pickup = pickup;
    monitor.putdown = putdown;
    monitor.test = test;
    monitor.init = init;
    monitor.output = output;
    monitor.init();
    for (int i = 0; i < N; i++){
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&id[i]);
    }
    for (int i = 0; i < N; i++){
        pthread_join(philosophers[i], NULL);
    }
    return 0;
}