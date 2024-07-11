#include <stdio.h>
#include <stdlib.h>

int main() {
    int *dynArr;
    int arrLen = 10;

    // 取得記憶體空間
    dynArr = malloc( arrLen * sizeof(int) );
    if( dynArr == NULL ) {
      fprintf(stderr, "Error: unable to allocate required memory\n");
      return 1;
    }

    // 擴充記憶體空間
    arrLen = 20;
    dynArr = realloc( dynArr, arrLen * sizeof(int) );

    // 確認有正常取得調整後的空間
    if( dynArr == NULL ) {
      fprintf(stderr, "Error: unable to allocate required memory\n");
      return 1;
    }

    // 使用動態取得的記憶體空間
    int i;
    for (i = 0; i < arrLen; ++i) {
      dynArr[i] = i;
      printf("%d ", dynArr[i]);
    }

    // 縮減記憶體空間
    arrLen = 5;
    dynArr = realloc( dynArr, arrLen * sizeof(int) );

    // 確認有正常取得調整後的空間
    if( dynArr == NULL ) {
      fprintf(stderr, "Error: unable to allocate required memory\n");
      return 1;
    }

    // 使用動態取得的記憶體空間
    for (i = 0; i < arrLen; ++i) {
      dynArr[i] = i;
      printf("%d ", dynArr[i]);
    }

    free(dynArr);
    return 0;
}