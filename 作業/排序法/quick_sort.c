#include <stdio.h>
#include "quick_sort.h"

void swap(int *v, int a, int b){
    if (a != b){
        int temp;
        temp = v[a];
        v[a] = v[b];
        v[b] = temp;
    }
}

void q_sort(int *array_to_sort, int *array_that_sorted_by, int start_index, int end_index){ //小到大
    while (start_index < end_index){
        int i = start_index;
        for (int j = start_index; j < end_index; j++){
            if(array_that_sorted_by[j] < array_that_sorted_by[end_index]){
                swap(array_to_sort, j, i);
                i++;
            }
        }
        swap(array_to_sort, end_index, i);

        if (i - start_index < end_index - i) {
            q_sort(array_to_sort, array_that_sorted_by, start_index, i - 1);  //對較小的分區進行 遞迴調用
            start_index = i + 1;              //對較大的分區使用 while 迭代
        } else {
            q_sort(array_to_sort, array_that_sorted_by, i + 1, end_index);    //同上
            end_index = i - 1;
        }
    }
}

void reverse_array(int *array, int start_index, int end_index){
    while (start_index < end_index) {   // 當 start 小於 end 時，繼續交換
        swap(array, start_index, end_index);    // 交換 start 和 end 指向的元素
        start_index++;    // 移動指標
        end_index--;
    }
}