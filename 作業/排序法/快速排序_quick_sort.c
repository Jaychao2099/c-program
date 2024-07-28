# include <stdio.h>
# include <stdlib.h>

void swap(int *v, int a, int b){
    int temp;
    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

/*
printf("i=%d, j=%d, ", i, j);
        printf("input[0~%d]=", num-1);
        for(int k = 0; k < num; k++){
            printf("%d ", input[k]);
        }
        printf("\n");
*/

void sort(int *input, int start, int end){
    if (start >= end)
        return;
    else {
        int i = start;
        for (int j = start; j < end; j++){
            if(input[j] < input[end]){
                swap(input, j, i);
                i++;
            }
        }
        swap(input, end, i);
        
        if (i < 1) i = 1;
        sort(input, 0, i-1);
        sort(input, i+1, end);
        return;
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

    sort(list, 0, count-1);

    printf("Sorted list:\n");
    for(int i = 0; i < count; i++){
        printf("%d ", list[i]);
    }

    free(list);

    return 0;
}