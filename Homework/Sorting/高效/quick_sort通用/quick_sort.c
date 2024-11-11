#include "C:\Users\joshu\文件\程式\c progrom\Homework\Sorting\quick_sort通用\quick_sort.h"  // 包含自己的標頭文件
#include <string.h>      // 提供 memcpy 函數的定義

// 泛型的交換函數，交換兩個元素的內容
void swap(void* array, int a, int b, size_t size) {
    if (a != b) {
        char temp[size];  // 使用 char 陣列進行交換
        void* va = (char*)array + a * size; // 計算 a 元素的地址
        void* vb = (char*)array + b * size; // 計算 b 元素的地址

        memcpy(temp, va, size);  // 把 a 元素複製到 temp
        memcpy(va, vb, size);    // 把 b 元素複製到 a
        memcpy(vb, temp, size);  // 把 temp 複製到 b
    }
}

// 泛型的快速排序函數
void quick_sort(void* array, int start, int end, size_t size, int (*cmp)(const void*, const void*)) {
    while (start < end) {
        int i = start;
        for (int j = start; j < end; j++) {
            if (cmp((char*)array + j * size, (char*)array + end * size) < 0) {  // 使用比較函數
                swap(array, j, i, size);
                i++;
            }
        }
        swap(array, end, i, size);

        if (i - start < end - i) {
            quick_sort(array, start, i - 1, size, cmp);  // 對較小的分區進行遞迴調用
            start = i + 1;                               // 對較大的分區使用 while 迭代
        } else {
            quick_sort(array, i + 1, end, size, cmp);    // 同上
            end = i - 1;
        }
    }
}

// 泛型的反轉數組函數
void reverse_array(void* array, int start_index, int end_index, size_t size) {
    while (start_index < end_index) {
        swap(array, start_index, end_index, size); // 使用泛型交換函數
        start_index++;
        end_index--;
    }
}