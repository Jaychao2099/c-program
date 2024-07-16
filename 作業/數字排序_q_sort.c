# include <stdio.h>
# include <stdlib.h>

void swap(int v[], int k){
    int temp;
    temp = v[k];
    v[k] = v[k+1];
    v[k+1] = temp;
}

void sort (int v[], int n){
    for (int i = 0; i < n; i += 1) {
        for (int j = i - 1; j >= 0 && v[j] > v[j + 1]; j -= 1){
            swap(v,j);
        }
    }
}

int main(){
    int count;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    int *list = malloc( (count+1) * sizeof(int) );

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