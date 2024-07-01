# include <stdio.h>

int main(){
    int m, n, p;
    printf("A(m*n) x B(n*p) = C(m*p)\n");

    printf("m = ");
    scanf("%d", &m);
    printf("n = ");
    scanf("%d", &n);
    printf("p = ");
    scanf("%d", &p);
    printf("A is a %d*%d matrix\nB is a %d*%d matrix\n", m, n, n, p);
    int A[m][n], B[n][p], C[m][p];

    printf("Enter elements in A by rows:\n");
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &A[i][j]);
        }
    }
    printf("Enter elements in B by rows:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < p; j++){
            scanf("%d", &B[i][j]);
        }
    }
    for (int i = 0; i < m; i++){ //乘法部分
        for (int j = 0; j < p; j++){
            C[i][j] = 0;  // 初始化 C[i][j]
            for (int k = 0; k < n; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    printf("Matrix C =\n");
    for (int i = 0; i < m; i++){
        for (int j = 0; j < p; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}