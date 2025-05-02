#ifndef AUTOFREE_H
#define AUTOFREE_H

#include <stdlib.h>

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

#endif // AUTOFREE_H


// 效果類似 atexit()，當變數超出作用域時，會自動釋放記憶體。
// 這樣可以避免記憶體洩漏，並且使程式碼更簡潔易讀。

// atexit() 是一個 C 標準函數，用於註冊一個函數，在程式結束時(c runtime)自動調用。
// 與 atexit() 不同的是，autofree 是在變數超出作用域時自動釋放記憶體，而不是在程式結束時。