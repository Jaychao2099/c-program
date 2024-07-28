# include <stdio.h>
# include <stdlib.h>

void swap(int *v, int a, int b){
    int temp;
    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void sort(int *input, int num){
    int i = 0;
    for (int j = 0; j < num - 1; j++){
        if(input[j] < input[num - 1]){
            swap(input, j, i);
            i++;
        }
    }
    if (i != 0) swap(input, num - 1, i);

    if (i >= num - 1)
        return;
    else {
        sort(input, i);
        sort(&input[i + 1], num - i -1);
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

    sort(list, count);

    printf("Sorted list:\n");
    for(int i = 0; i < count; i++){
        printf("%d ", list[i]);
    }

    free(list);

    return 0;
}