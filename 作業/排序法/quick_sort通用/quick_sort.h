#ifndef QUICK_SORT_H  // 避免重複包含
#define QUICK_SORT_H

#include <stddef.h>  // 提供 size_t 類型的定義

// 泛型的交換函數
void swap(void* array, int a, int b, size_t size);

// 泛型的快速排序函數
void quick_sort(void* array, int start, int end, size_t size, int (*cmp)(const void*, const void*));

// 泛型的反轉函數
void reverse_array(void* array, int start_index, int end_index, size_t size);

#endif  // QUICK_SORT_H