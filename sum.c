#include <stdio.h>

int main()
{   int integer1;
    int integer2;
    int sum;
    printf("num1: ");
    scanf("%d", integer1);
    printf("num2: ");
    scanf("%d", integer2);
    sum = integer1 + integer2;
    printf("Sum is %d \n", sum);
    return 0;
}