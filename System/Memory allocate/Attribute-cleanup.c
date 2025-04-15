#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
autofree 是一個巨集，用於自動釋放記憶體。它使用了 GCC 的 __attribute__ 屬性，並指定了 cleanup(free_stack) 作為清理函數。
這意味著當變數超出作用域時，free_stack 函數會自動被調用來釋放記憶體。
*/
#define autofree \
    __attribute__((cleanup(free_stack)))

// always_inline 是 GCC 的一個屬性，用於強制編譯器內聯函數，即使它可能不符合內聯的條件。
__attribute__ ((always_inline))

// free_stack 是一個內聯函數，用於釋放指向 stack 的指針所指向的記憶體。這樣可以在變數超出作用域時自動釋放記憶體，避免記憶體洩漏。
inline void free_stack(void *ptr) { free(*(void **) ptr); }


int main(void) {
    autofree int *i = malloc(sizeof (int));
    *i = 1;
    return *i;
}
