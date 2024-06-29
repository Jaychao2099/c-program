# include<stdio.h>

int main(){
    int count, input, max, min;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    printf("Enter the list:\n");
    for(int i = 1; i <= count; i++) {
        scanf("%d", &input);
        if (i == 1){
            max = input;
            min = input;
        }
        max = max > input ? max : input;
        min = min < input ? min : input;
    }
    printf("\nThe maximum is %d\nThe minimum is %d\n", max, min);
    return 0;
}