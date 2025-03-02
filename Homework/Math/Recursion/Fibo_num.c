# include <stdio.h>
# include <stdlib.h>

int fibo_iter(int x){
    int a = 0, b = 1;
    for (int i = 0; i < x; i++){
        int tmp = a;
        a = b;
        b += tmp;
    }
    return a;
}

int fibo_rec(int x){
    if (x == 0) return 0;
    if (x == 1) return 1;
    return fibo_rec(x - 1) + fibo_rec(x - 2);
}


int fibo_tail_rec(int x, int a, int b){
    if (x == 0) return a;
    if (x == 1) return b;
    return fibo_tail_rec(x - 1, b, a + b);
}

// long long fibo_num_analysis(long long n){
//     return ((4 << (n * (3+n))) / ((4 << (2*n)) - (2 << n) - 1)) & ((2 << n) - 1);
// }

int **matrix_multiply(int **a, int **b) {
    int **t = malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++) {
        t[i] = malloc(sizeof(int) * 2);
        t[i][0] = 0;
        t[i][1] = 0;
    }
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                t[i][j] += a[i][k] * b[k][j];
    return t;
}

int **matrix_pow(int **a, int n) {
    if (n == 1) return a;
    if (n % 2 == 0) {
        int **t = matrix_pow(a, n >> 1);
        return matrix_multiply(t, t);
    } else {
        int **t1 = matrix_pow(a, n >> 1);
        int **t2 = matrix_multiply(t1, t1);
        return matrix_multiply(t2, a);
    }
}

int fibo_Q_matrix(int n) {
    if (n <= 0) return 0;
    int **A1 = malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++) A1[i] = malloc(sizeof(int) * 2);
    A1[0][0] = 1;   A1[0][1] = 1;
    A1[1][0] = 1;   A1[1][1] = 0;

    int **result = matrix_pow(A1, n);
    int fib_n = result[0][1];

    // // 釋放記憶體
    // for (int i = 0; i < 2; i++) {
    //     free(A1[i]);
    //     free(result[i]);
    // }
    // free(A1);
    // free(result);

    return fib_n;
}

int fibo_fast_doubling(int n) {
    if (n == 0) return 0;
    int t0 = 1; // F(n)
    int t1 = 1; // F(n + 1)
    int t3 = 1; // F(2n)
    int t4; // F(2n+1)
    int i = 1;
    while (i < n) {
        if ((i << 1) <= n) {
            t4 = t1 * t1 + t0 * t0;
            t3 = t0 * (2 * t1 - t0);
            t0 = t3;
            t1 = t4;
            i = i << 1;
        } else {
            t0 = t3;
            t3 = t4;
            t4 = t0 + t4;
            i++;
        }
    }
    return t3;
}

int main(){
    int num;

    printf("Number: ");
    if (scanf("%d", &num) != 1 || num < 1){
        printf("Input error, must >= 1");
        return 1;
    }

    printf("Fibo[%d] = %d (iter)\n", num, fibo_iter(num));
    printf("Fibo[%d] = %d (recurse)\n", num, fibo_rec(num));
    printf("Fibo[%d] = %d (tail recurse)\n", num, fibo_tail_rec(num, 0, 1));
    // printf("Fibo[%d] = %d (number analysis)\n", num, fibo_num_analysis((long long)num));
    printf("Fibo[%d] = %d (Q matrix)\n", num, fibo_Q_matrix(num));
    printf("Fibo[%d] = %d (fast doubling)\n", num, fibo_fast_doubling(num));
    return 0;
}