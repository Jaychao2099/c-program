# include <stdio.h>
# include <stdlib.h>

# define BUCKETSIZE 10

typedef struct Bucket{
    int *bucket;
    int size;
}Bucket;

void swap(int *v, int k, int l){
    int temp = v[k];
    v[k] = v[l];
    v[l] = temp;
}

void insertion_sort(int *list, int n){
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0 && list[j] > list[j + 1]; j--){
            swap(list, j, j + 1);
        }
    }
}

void bucket_sort(int *list, int n, int range1, int range2){
    int k = (range2 - range1 + 1) / BUCKETSIZE;
    Bucket *b = malloc(k * sizeof(Bucket));
    for (int i = 0; i < k; i++){
        b[i].bucket = malloc(BUCKETSIZE * sizeof(int));
        b[i].size = 0;
    }

    for (int i = 0; i < n; i++){
        int hash = (list[i] - range1) / BUCKETSIZE;
        b[hash].bucket[(b[hash].size)++] = list[i];
    }

    for (int i = 0; i < k; i++){
        if (b[i].size > 0){
            insertion_sort(b[i].bucket, b[i].size);
        }
    }

    int temp_index = 0;
    for (int i = 0; i < k; i++){
        for (int j = 0; j < b[i].size; j++){
            list[temp_index++] = b[i].bucket[j];
        }
    }
}

int main(){
    int count, range_1, range_2;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    printf("Enter the range of list: (start end)");
    scanf("%d%d", &range_1, &range_2);

    int *list = malloc(count * sizeof(int));

    printf("Enter the list: ");
    for(int i = 0; i < count; i++){
        scanf("%d", &list[i]);
    }

    bucket_sort(list, count, range_1, range_2);

    printf("Sorted list:\n");
    for(int i = 0; i < count; i++){
        printf("%d ", list[i]);
    }

    free(list);

    return 0;
}