# include <stdio.h>
# include <stdlib.h>

static inline void swap(int *v, int a, int b){
    if (a != b){
        int temp;
        temp = v[a];
        v[a] = v[b];
        v[b] = temp;
    }
}

// static void q_sort(int *list, int start, int end){
//     while (start < end){
//         int i = start;
//         for (int j = start; j < end; j++){
//             if(list[j] < list[end]){      // end 當 pivot
//                 swap(list, j, i);
//                 i++;
//             }
//         }
//         swap(list, end, i);

//         if (i - start < end - i) {
//             q_sort(list, start, i - 1);  //對較小的分區進行 遞迴調用
//             start = i + 1;                //對較大的分區使用 while 迭代
//         } else {
//             q_sort(list, i + 1, end);    //同上
//             end = i - 1;
//         }
//     }
// }

static void q_sort(int *list, int start, int end){ 
    if (start >= end) return;

    int pivot = list[start];    //(start + end) / 2; // 使用 list[mid] 作為 pivot 值
    int i = start, j = end;
    while (i <= j){
        while (list[i] < pivot) i++;    // 找到左側大於 pivot 的元素
        while (list[j] > pivot) j--;    // 找到右側小於 pivot 的元素
        if (i <= j){           // 如果 i < j，則交換位置
            swap(list, i, j);
            i++;
            j--;
        }
    }
    q_sort(list, start, j); // 處理左側
    q_sort(list, i, end);   // 處理右側
}

int main(){
    int count;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    int *list = malloc(count * sizeof(int));

    printf("Enter the list: ");
    for(int i = 0; i < count; i++){
        scanf("%d", &list[i]);
    }

    q_sort(list, 0, count-1);

    printf("Sorted list:\n");
    for(int i = 0; i < count; i++){
        printf("%d ", list[i]);
    }

    free(list);

    return 0;
}