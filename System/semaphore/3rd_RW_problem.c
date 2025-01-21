#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t r_mutex;
sem_t resource;
sem_t service_queue;    // 形成了一個FIFO的隊列, 避免某類執行緒(R or W)長期被忽略
int readcount = 0;

void *reader(void *arg){
    int id = *(int *)arg;
    while (1){
        sem_wait(&service_queue);       // 進入service_queue
            pthread_mutex_lock(&r_mutex);
                readcount++;
                if (readcount == 1) sem_wait(&resource);    // 第一個reader, wait(resource), 確保reader不會被其他writer打斷
            pthread_mutex_unlock(&r_mutex);
        sem_post(&service_queue);       // 離開service_queue
        
        printf("Reader %d is reading\n", id);

        pthread_mutex_lock(&r_mutex);
            readcount--;
            if (readcount == 0) sem_post(&resource);        // 最後一個reader, signal(resource), 釋放資源, 讓其他writer可以進入
        pthread_mutex_unlock(&r_mutex);
    }
}

void *writer(void *arg){
    int id = *(int *)arg;
    while (1){
        sem_wait(&service_queue);    // 進入service_queue
            sem_wait(&resource);            // wait(resource), 等待獲取資源, 確保writer不會被其他writer打斷
        sem_post(&service_queue);    // 離開service_queue
        
        printf("Writer %d is writing\n", id);

        sem_post(&resource);        // signal(resource), 釋放資源, 讓其他writer或reader可以進入
    }
}

int main(){
    pthread_t reader_thread[5], writer_thread[5];
    int reader_id[5], writer_id[5];

    sem_init(&resource, 0, 1);
    sem_init(&service_queue, 0, 1);
    pthread_mutex_init(&r_mutex, NULL);

    for (int i = 0; i < 5; i++){
        reader_id[i] = i;
        writer_id[i] = i;
        pthread_create(&reader_thread[i], NULL, reader, (void *)&reader_id[i]);
        pthread_create(&writer_thread[i], NULL, writer, (void *)&writer_id[i]);
    }

    for (int i = 0; i < 5; i++){
        pthread_join(reader_thread[i], NULL);
        pthread_join(writer_thread[i], NULL);
    }

    return 0;
}
