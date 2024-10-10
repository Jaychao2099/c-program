# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAXSIZE 1023   // 10 層
# define ARRAYSIZE sizeof(array) / sizeof(array[0])

typedef struct heap{
    int *array;
    int size;
}heap;

void print_heap(heap *h){
    int last = 0;
    for (int i = 0; i < h->size; i++){
        printf("%d", h->array[i]);
        if (i == last || i == h->size - 1){
            printf("\n");
            last = 2 * last + 2;
        }
        else printf(" ");
    }
}

_Bool heap_full(heap *h){
    if (h->size == MAXSIZE){
        printf("ERROR: Heap is full\n");
        return 1;
    }
    return 0;
}

_Bool heap_empty(heap *h){
    if (!h->size){
        printf("ERROR: Heap is empty\n");
        return 1;
    }
    return 0;
}

void insert_maxheap(heap *h, int var){
    if (heap_full(h)){
        printf("ERROR: cannot insert element\n");
        return;
    }
    int i = h->size++;
    while (i && var > h->array[(i - 1) / 2]){   // 到 root 了 or 比不過了 => 跳出
        h->array[i] = h->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->array[i] = var;
}

int delete_maxheap(heap *h){
    if (heap_empty(h)){
        printf("ERROR: cannot delete element\n");
        return 0;
    }
    int x = h->array[0];
    int temp = h->array[--h->size];             // 最後一格提取出來當root 往下比大小
    int parent = 0;
    int child = 1;       // left child
    while (child < h->size){
        if (child < h->size - 1)
            if (h->array[child] < h->array[child + 1]) child++; // j change to right child
        if (temp > h->array[child]) break;          // 比完了
        h->array[parent] = h->array[child];
        parent = child;              // i to new parent
        child = 2 * child + 1;      // j to left child
    }
    h->array[parent] = temp;
    return x;
}

void create_maxheap_bottom_up(heap *h, int *data){
    h->array = malloc(MAXSIZE * sizeof(int));
    for (int i = h->size / 2 - 1; i > -1; i--){     // 先到最後一個parent
        int temp = data[i];             // 先暫存，之後放到正確位置
        int child = 2 * i + 1;
        while(child < h->size){         // 還有child
            if (child < h->size - 1)
                if (data[child] < data[child + 1]) child++;
            if (temp > data[child]) break;          // 比完了
            data[(child - 1) / 2] = data[child];    // 沒比贏，下面換上來
            child = 2 * child + 1;      // to left child
        }
        data[(child - 1) / 2] = temp;   // while loop最後，child多下一層，現在返回
    }
    memcpy(h->array, data, h->size * sizeof(int));
}

int main(){
    int data[] = {1, 3, 2, 4, 5, 6};
    heap *h = malloc(sizeof(heap));
    h->size = sizeof(data) / sizeof(data[0]);
    
    create_maxheap_bottom_up(h, data);
    // insert_maxheap(h, 20);
    // insert_maxheap(h, 15);
    // insert_maxheap(h, 2);
    // insert_maxheap(h, 14);
    // insert_maxheap(h, 10);
    print_heap(h);

    printf("\n");
    insert_maxheap(h, 21);
    print_heap(h);

    printf("\n");
    delete_maxheap(h);
    print_heap(h);

    free(h->array);
    free(h);
    return 0;
}