#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty;
sem_t full;

void wait_(sem_t *sem){
    sem_wait(sem);
}

void signal_(sem_t *sem){
    sem_post(sem);
}

void producer(void *arg){
    int *buffer = (int *)arg;
    int in = 0;
    int item = 0;
    while(1){
        wait_(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        in = (in + 1) % N;
        pthread_mutex_unlock(&mutex);
        signal_(&full);
        item++;
    }
}

void consumer(void *arg){
    int *buffer = (int *)arg;
    int out = 0;
    int item;
    while(1){
        wait_(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        out = (out + 1) % N;
        pthread_mutex_unlock(&mutex);
        signal_(&empty);
        printf("Consumer: %d\n", item);
    }
}

int main(){
    int *buffer = malloc(N * sizeof(int));
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 1, N);
    sem_init(&full, 1, 0);

    pthread_create(&producer_thread, NULL, (void *)producer, (void *)buffer);
    pthread_create(&consumer_thread, NULL, (void *)consumer, (void *)buffer);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    free(buffer);
    return 0;
}