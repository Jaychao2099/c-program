# include <stdio.h>
# include <stdlib.h>

void swap(int *v, int a, int b){
    if (a != b){
        int temp;
        temp = v[a];
        v[a] = v[b];
        v[b] = temp;
    }
}

void sort(int *input, int start, int end){
    while (start < end){
        int i = start;
        for (int j = start; j < end; j++){
            if(input[j] < input[end]){
                swap(input, j, i);
                i++;
            }
        }
        swap(input, end, i);

        if (i - start < end - i) {
            sort(input, start, i - 1);  //對較小的分區進行 遞迴調用
            start = i + 1;              //對較大的分區使用 while 迭代
        } else {
            sort(input, i + 1, end);    //同上
            end = i - 1;
        }

        //sort(input, 0, i-1);
        //sort(input, i+1, end);
        //return;
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