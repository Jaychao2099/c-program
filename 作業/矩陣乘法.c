# include <stdio.h>
# include <string.h>
# include <stdlib.h>

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
    size_t max_length[p];
    char matrix_num[m][p][20];

    // 初始化 max_length 數組
    for (int j = 0; j < p; j++) {
        max_length[j] = 0;
    }

    // 求該column 最長字串長度
    for (int j = 0; j < p; j++){
        for (int i = 0; i < m; i++){
            sprintf(matrix_num[i][j], "%d", C[i][j]); // 矩陣 int 換成 string
            size_t len = strlen(matrix_num[i][j]);
            if (len > max_length[j]) {
                max_length[j] = len;
            }
        }
    }

    printf("Matrix C =\n");
    for (int i = 0; i < m; i++){
        for (int j = 0; j < p; j++){
            size_t space_length = max_length[j] - strlen(matrix_num[i][j]);
            for (int k = 0; k < space_length; k++){  //用space 對齊
                printf(" ");
            }
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}