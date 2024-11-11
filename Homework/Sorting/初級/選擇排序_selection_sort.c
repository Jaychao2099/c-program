# include <stdio.h>
# include <stdlib.h>

static inline void swap(int *v, int k, int l){
    int temp = v[k];
    v[k] = v[l];
    v[l] = temp;
}

void selection_sort(int *list, int n){
    for (int i = 0; i < n-1; i++){
        int min_index = i;
        for(int j = i+1; j < n; j++){
            if (list[j] < list[min_index]){
                min_index = j;
            }
        }
        if(min_index != i){
            swap(list, i, min_index);
        }
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

    selection_sort(list, count);

    printf("Sorted list:");
    for(int i = 0; i < count; i++){
        printf(" %d", list[i]);
    }
    
    free(list);

    return 0;
}