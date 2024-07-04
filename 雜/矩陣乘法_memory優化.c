#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void multiply_matrices(int **A, int **B, int **C, size_t m, size_t n, size_t p) {
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < p; j++) {
            C[i][j] = 0;
            for (size_t k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void print_matrix(int **C, size_t m, size_t p) {
    size_t max_length[p];
    char ***matrix_num = malloc(m * sizeof(char **));
    for (size_t i = 0; i < m; i++) {
        matrix_num[i] = malloc(p * sizeof(char *));
        for (size_t j = 0; j < p; j++) {
            matrix_num[i][j] = malloc(20 * sizeof(char));
        }
    }

    for (size_t j = 0; j < p; j++) {
        max_length[j] = 0;
        for (size_t i = 0; i < m; i++) {
            snprintf(matrix_num[i][j], 20, "%d", C[i][j]);
            size_t len = strlen(matrix_num[i][j]);
            if (len > max_length[j]) {
                max_length[j] = len;
            }
        }
    }

    printf("Matrix C =\n");
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < p; j++) {
            size_t space_length = max_length[j] - strlen(matrix_num[i][j]);
            for (size_t k = 0; k < space_length; k++) {
                printf(" ");
            }
            printf("%s ", matrix_num[i][j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < p; j++) {
            free(matrix_num[i][j]);
        }
        free(matrix_num[i]);
    }
    free(matrix_num);
}

int main() {
    size_t m, n, p;
    printf("A(m*n) x B(n*p) = C(m*p)\n");

    printf("m = ");
    scanf("%zu", &m);
    printf("n = ");
    scanf("%zu", &n);
    printf("p = ");
    scanf("%zu", &p);

    if (m == 0 || n == 0 || p == 0) {
        printf("Invalid matrix dimensions\n");
        return 1;
    }

    printf("A is a %zu*%zu matrix\nB is a %zu*%zu matrix\n", m, n, n, p);

    int **A = malloc(m * sizeof(int *));
    int **B = malloc(n * sizeof(int *));
    int **C = malloc(m * sizeof(int *));

    for (size_t i = 0; i < m; i++) {
        A[i] = malloc(n * sizeof(int));
        C[i] = calloc(p, sizeof(int));
    }
    for (size_t i = 0; i < n; i++) {
        B[i] = malloc(p * sizeof(int));
    }

    printf("Enter elements in A by rows:\n");
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements in B by rows:\n");
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < p; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    multiply_matrices(A, B, C, m, n, p);
    print_matrix(C, m, p);

    for (size_t i = 0; i < m; i++) {
        free(A[i]);
        free(C[i]);
    }
    for (size_t i = 0; i < n; i++) {
        free(B[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}