# include <stdio.h>
# include <stdlib.h>

# define MAXSIZE 1023   // 10 層

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
    int i = 0, j = 1;       // j is left child
    while (i <= h->size){
        if (h->array[j] < h->array[j + 1])      // j change to right child
            j++;
        if (temp > h->array[j]) break;          // 比完了
        h->array[i] = h->array[j];
        i = j;              // i to new parent
        j = 2 * j + 1;      // j to left child
    }
    h->array[i] = temp;
    return x;
}

int main(){
    heap *h = calloc(1, sizeof(heap));
    h->array = malloc(MAXSIZE * sizeof(int));
    insert_maxheap(h, 20);
    insert_maxheap(h, 15);
    insert_maxheap(h, 2);
    insert_maxheap(h, 14);
    insert_maxheap(h, 10);
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