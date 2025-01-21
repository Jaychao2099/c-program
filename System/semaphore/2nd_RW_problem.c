#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t r_mutex, w_mutex;
sem_t read_try, resource;
int readcount = 0, writecount = 0;

static inline void wait_(sem_t *sem){sem_wait(sem);}

static inline void signal_(sem_t *sem){sem_post(sem);}

void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {
        wait_(&read_try);
            pthread_mutex_lock(&r_mutex);
                readcount++;
                if (readcount == 1) wait_(&resource);
            pthread_mutex_unlock(&r_mutex);
        signal_(&read_try);
        
        printf("Reader %d is reading\n", id);

        pthread_mutex_lock(&r_mutex);
            readcount--;
            if (readcount == 0) signal_(&resource);
        pthread_mutex_unlock(&r_mutex);
    }
}

void *writer(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&w_mutex);
            writecount++;
            if (writecount == 1) wait_(&read_try);
        pthread_mutex_unlock(&w_mutex);

        wait_(&resource);
            printf("Writer %d is writing\n", id);
        signal_(&resource);

        pthread_mutex_lock(&w_mutex);
            writecount--;
            if (writecount == 0) signal_(&read_try);
        pthread_mutex_unlock(&w_mutex);
    }
}

int main(){
    pthread_t reader_thread[5], writer_thread[5];
    int reader_id[5], writer_id[5];

    sem_init(&read_try, 0, 1);
    sem_init(&resource, 0, 1);
    pthread_mutex_init(&r_mutex, NULL);
    pthread_mutex_init(&w_mutex, NULL);

    for (int i = 0; i < 5; i++) {
        reader_id[i] = i;
        writer_id[i] = i;
        pthread_create(&reader_thread[i], NULL, reader, &reader_id[i]);
        pthread_create(&writer_thread[i], NULL, writer, &writer_id[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(reader_thread[i], NULL);
        pthread_join(writer_thread[i], NULL);
    }

    return 0;
}

