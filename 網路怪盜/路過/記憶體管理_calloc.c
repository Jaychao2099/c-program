#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int *dynArr;
    int arrLen = 10;

    // 配置記憶體，並初始化
    dynArr = calloc( arrLen, sizeof(int) );

    if( dynArr == NULL ) {
        fprintf(stderr, "Error: unable to allocate required memory\n");
        return 1;
    }
    
    for (size_t i = 0; i < arrLen; ++i) {
    printf("%d ", dynArr[i]);
    }

    free(dynArr);

    return 0;
}