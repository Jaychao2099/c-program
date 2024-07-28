# include <stdio.h>
# include <stdlib.h>

int main(){
    int count;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    int *list = malloc( (count+1) * sizeof(int) );



    free(list);
    return 0;
}