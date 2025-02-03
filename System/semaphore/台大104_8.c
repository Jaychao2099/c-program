#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // 5 個人
#define CHAIRS 4  // 4 張椅子
#define ROUNDS 3  // 3 輪內至少要坐 1 次

sem_t chairs;  // 控制 4 張椅子的信號量
pthread_mutex_t lock;  // 保護變數的互斥鎖
int wins[N] = {0};  // 記錄每個人過去 3 輪的成功次數
int round = 0;  // 當前輪數

void* person(void* arg) {
    int id = *(int*)arg;

    while(1) {  // 總共 9 輪測試
        pthread_mutex_lock(&lock);
        
        // 如果該人過去 3 輪都沒贏，則優先入座
        _Bool need_to_win = (wins[id] == 0 && round % ROUNDS == 0);
        
        pthread_mutex_unlock(&lock);

        if (need_to_win) {
            sem_wait(&chairs);  // 強制入座
        } else {
            if (sem_trywait(&chairs) != 0) {
                // 沒拿到椅子，表示輸了
                continue;
            }
        }

        // 取得椅子，進入臨界區
        pthread_mutex_lock(&lock);
        wins[id]++;  // 記錄這一輪有入座
        pthread_mutex_unlock(&lock);

        printf("Person %d sits in round %d.\n", id, round);

        sleep(1); // 模擬坐一會兒

        // 離開臨界區，釋放椅子
        sem_post(&chairs);
    }
    return NULL;
}

int main() {
    pthread_t people[N];
    int ids[N];

    sem_init(&chairs, 0, CHAIRS);
    pthread_mutex_init(&lock, NULL);

    // 創建 5 個人
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&people[i], NULL, person, &ids[i]);
    }

    // 控制 9 輪比賽
    for (round = 0;; round++) {
        sleep(2); // 每輪間隔 2 秒
        pthread_mutex_lock(&lock);
        
        // 每 3 輪重置 wins 記錄
        if (round % ROUNDS == 0) {
            for (int i = 0; i < N; i++) {
                wins[i] = 0;
            }
        }

        printf("==== Round %d ends ====\n", round);
        pthread_mutex_unlock(&lock);
    }

    // 等待所有人結束
    for (int i = 0; i < N; i++) {
        pthread_join(people[i], NULL);
    }

    sem_destroy(&chairs);
    pthread_mutex_destroy(&lock);

    return 0;
}
