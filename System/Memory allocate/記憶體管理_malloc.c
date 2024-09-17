#include <stdio.h>
#include <stdlib.h>

int main() {
    int **dynArr;

    // 指定空間大小
    int arrLen1 = 10;
    int arrLen2 = 5;

    // 取得記憶體空間
    dynArr = (int **)malloc( arrLen1 * sizeof(int *) );
    for (int i = 0; i < arrLen1; i++) {
        dynArr[i] = (int *)malloc(arrLen2 * sizeof(int));
    }

    if( dynArr == NULL ) {
        fprintf(stderr, "Error: unable to allocate required memory\n");
        return 1;
    }

    // 使用動態取得的記憶體空間
    for (size_t i = 0; i < arrLen1; ++i) {
        for (size_t j = 0; j < arrLen2; ++j) {
            int index = i * arrLen2 + j;
            /*
            dynArr[index] = index;
            printf("[%d][%d] = dynArr[%d] = %d, add = \n", i, j, index, dynArr[index]);
            */
            dynArr[i][j] = index;
            printf("dynArr[%d][%d] = %d, addr = %x\n", i, j, dynArr[i][j], &dynArr[i][j]);
        }
    }

    // 釋放記憶體空間
    for (int i = 0; i < arrLen1; i++) {
        free(dynArr[i]);  // 釋放每一行
    }
    free(dynArr);

    return 0;
    }