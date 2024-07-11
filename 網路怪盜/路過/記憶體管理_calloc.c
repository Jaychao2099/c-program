#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* dynArr_char;
    int* dynArr_int;
    int arrLen = 5;

    // 配置記憶體，並初始化
    dynArr_char = calloc( arrLen, sizeof(char) );
    dynArr_int = calloc( arrLen, sizeof(int) );

    if( dynArr_char == NULL || dynArr_int == NULL  ) {
        fprintf(stderr, "Error: unable to allocate required memory\n");
        return 1;
    }
    
    for (size_t i = 0; i < arrLen; ++i) {
    printf("dynArr_char[%d] = \"%c\", dynArr_int[%d] = \"%d\"\n", i, dynArr_char[i], i, dynArr_int[i]);
    }

    free(dynArr_char);
    free(dynArr_int);

    return 0;
}