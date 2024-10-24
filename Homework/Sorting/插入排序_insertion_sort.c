# include <stdio.h>
# include <stdlib.h>

void swap(int *v, int k, int l){
    int temp = v[k];
    v[k] = v[l];
    v[l] = temp;
}

void sort(int *v, int n){
    for (int i = 0; i < n; i++){
        for (int j = i - 1; j >= 0 && v[j] > v[j + 1]; j--){
            swap(v,j, j + 1);
        }
    }
}

int main(){
    int count;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    int *list = malloc( (count) * sizeof(int) );

    printf("Enter the list: \n");
    for(int i = 0; i < count; i++){
        scanf("%d", &list[i]);
    }

    sort(list, count);
    
    printf("Sorted list:");
    for(int i = 0; i < count; i++){
        printf(" %d", list[i]);
    }

    free(list);

    return 0;
}