// gcc -O3 -o 快速開方 快速開方.c -lm

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define NUM_TESTS 1000000
#define MAX_VALUE 1000.0

float FastSqrt_32(float x){
    unsigned int x_bit = 0;              // 定義一個 32位無符號整數 變量 x_bit
    x_bit = *((unsigned int*) &x);       // 通過指針操作直接訪問 x 的內存, 並將其解釋為無符號整數
    x_bit = (x_bit >> 1) + 0x1fbb4f2e;
    return *((float*) &x_bit);
}

double FastSqrt_64(double x) {
    unsigned long long i;
    double y;
    const double threehalfs = 1.5f;

    y = x;
    i = *(unsigned long long*)&y;
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y = *(double*)&i;
    for (int i = 0; i < 1; i++)
    y *= (threehalfs - ((x * 0.5f) * y * y));  // 可以再次迭代以提高精度

    return x * y;
}

int main(){
    double *test_values = malloc(NUM_TESTS * sizeof(double));
    LARGE_INTEGER frequency, start, end;
    double time_used;

    QueryPerformanceFrequency(&frequency);

    // 生成測試數據
    srand((unsigned int)time(NULL));
    for (int i = 0; i < NUM_TESTS; i++) {
        test_values[i] = ((double)rand() / RAND_MAX) * MAX_VALUE;
    }

    // 測試 FastSqrt_64
    QueryPerformanceCounter(&start);
    for (int i = 0; i < NUM_TESTS; i++) {
        volatile double result = FastSqrt_64(test_values[i]);
    }
    QueryPerformanceCounter(&end);
    time_used = (double)(end.QuadPart - start.QuadPart) * 1e6 / frequency.QuadPart;
    printf("FastSqrt_64() time:\t%8.2f ms\n", time_used);

    // 測試標準庫 sqrt
    QueryPerformanceCounter(&start);
    for (int i = 0; i < NUM_TESTS; i++) {
        volatile double result = sqrt(test_values[i]);
    }
    QueryPerformanceCounter(&end);
    time_used = (double)(end.QuadPart - start.QuadPart) * 1e6 / frequency.QuadPart;
    printf("<math.h> sqrt() time:\t%8.2f ms\n", time_used);

    // 計算並打印誤差
    double total_error = 0.0;
    for (int i = 0; i < NUM_TESTS; i++) {
        double fast_result = FastSqrt_64(test_values[i]);
        double std_result = sqrt(test_values[i]);
        total_error += fabs(fast_result - std_result) / std_result;
    }
    double avg_error = total_error / NUM_TESTS;
    printf("FastSqrt_64 average bias: %f%%\n", avg_error * 100);

    free(test_values);
    return 0;

    // float a;
    // printf("enter float: ");
    // scanf("%f", &a);
    // float result_32 = FastSqrt_32(a);
    // printf("%f\n", result_32);

    // double b = (double)a;
    // double result_64 = FastSqrt_64(b);
    // printf("%lf\n", result_64);

    // printf("sqrt() = %lf\n", sqrt(b));

    return 0;
}