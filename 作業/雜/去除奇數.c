# include <stdio.h>
# include <math.h>
# include <stdlib.h>

int main(){
    int num, *list, *ptr;
    printf("Enter the max number: ");
    scanf("%d", &num);

    list = (int *)malloc(num * sizeof(int));
    for (int i = 0 ; i < num; i++) list[i] = i + 1;

    int temp = 1;
    for (int i = 0; i < log(num)+1; i++){
        printf("%d:", i + 1);
        for (int j = temp-1; j < num; j += temp){
            if ((j / temp) % 2 == 0){
                list[j] = 0;
            }
        }
        temp *= 2;
        for (int j = 0; j < num; j++) printf(" %d", list[j]);
        printf("\n");
    }

    free(list);

    return 0;
}