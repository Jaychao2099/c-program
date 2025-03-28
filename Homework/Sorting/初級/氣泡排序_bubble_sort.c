# include <stdio.h>
# include <stdlib.h>

static inline void swap(int *v, int k, int l){
    int temp = v[k];
    v[k] = v[l];
    v[l] = temp;
}

void bubble_sort(int *list, int n){
    for (int i = 0; i < n; i++){
        // _Bool noswap = 1;
        for (int j = n-1; j > i; j--){
            if (list[j] < list[j-1]){
                swap(list, j, j-1);
                // noswap = 0;
            }
        }
        // if (noswap) return;
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

    bubble_sort(list, count);

    printf("Sorted list:");
    for(int i = 0; i < count; i++){
        printf(" %d", list[i]);
    }
    
    free(list);

    return 0;
}