#include <stdio.h>
#include "C:\Users\joshu\文件\程式\c progrom\Homework\Sorting\quick_sort通用\quick_sort.h"  // 包含泛型快速排序的標頭文件

// 整數的比較函數
int int_cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// 測試用的結構體
typedef struct {
    int id;
    double value;
} Item;

// 比較Item結構的函數
int item_cmp(const void* a, const void* b) {
    const Item* itemA = (const Item*)a;
    const Item* itemB = (const Item*)b;
    // 比較id字段
    return itemA->id - itemB->id;
}

int main() {
    // 使用整數數組
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int length = sizeof(arr) / sizeof(arr[0]);

    // 使用整數數組進行排序
    quick_sort(arr, 0, length - 1, sizeof(int), int_cmp);
    printf("Sorted int array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 使用自定義結構數組
    Item items[] = {{1, 2.0}, {2, 1.0}, {3, 3.0}, {0, 4.0}};
    int itemLength = sizeof(items) / sizeof(items[0]);

    // 使用自定義結構數組進行排序
    quick_sort(items, 0, itemLength - 1, sizeof(Item), item_cmp);
    printf("Sorted Item array by id:\n");
    for (int i = 0; i < itemLength; i++) {
        printf("{id: %d, value: %.1f} \n", items[i].id, items[i].value);
    }
    printf("\n");

    return 0;
}
