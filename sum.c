#include <stdio.h>
int main()
{   int integer1;
    int integer2;
    int sum;
    printf("請輸入數字1: ");
    scanf("%d", integer1);
    printf("請輸入數字2: ");
    scanf("%d", integer2);
    sum = integer1 + integer2;
    printf("總和是 %d \n", sum);
    return 0;
}