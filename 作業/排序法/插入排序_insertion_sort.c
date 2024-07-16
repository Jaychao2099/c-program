# include <stdio.h>
# include <stdlib.h>

void swap(int v[], int k){
    int temp;
    temp = v[k];
    v[k] = v[k+1];
    v[k+1] = temp;
}

void sort (int v[], int n){
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0 && v[j] > v[j + 1]; j--){
            swap(v,j);
            //printf("i=%d, j=%d, %d %d %d %d %d %d %d\n", i, j, v[0], v[1], v[2], v[3], v[4], v[5], v[6]);
        }
        //printf("-------\n");
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