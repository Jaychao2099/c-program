# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void adjust_max(int *data, int subroot_index, int size){
    int temp = data[subroot_index];             // 先暫存，之後放到正確位置
    int child = 2 * subroot_index + 1;
    while(child < size){            // 還有child
        if (child + 1 < size && data[child] < data[child + 1]) child++; // 變right child
        if (temp >= data[child]) break;         // 比完了
        data[subroot_index] = data[child];      // 沒比贏，下面換上來
        subroot_index = child;                  // 更新 subroot_index
        child = 2 * subroot_index + 1;          // to left child
    }
    data[(child-1) / 2] = temp;     // while loop最後，child多下一層，現在返回
}

void create_maxheap_bottom_up(int *data, int size){
    for (int i = size/2 - 1; i > -1; i--){     // 先到最後一個parent
        adjust_max(data, i, size);
    }
}

int delete_maxheap(int *heap, int *size){
    int x = heap[0];   // 返回值
    heap[0] = heap[--(*size)];
    adjust_max(heap, 0, *size);
    return x;
}

void heap_sort(int *list, int n){
    create_maxheap_bottom_up(list, n);
    while (n > 1){
        list[n-1] = delete_maxheap(list, &n);
    }
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

    heap_sort(list, count);

    printf("Sorted list:\n");
    for(int i = 0; i < count; i++){
        printf("%d ", list[i]);
    }

    free(list);

    return 0;
}