#include <stdio.h>

int main()
{   int integer1;
    int integer2;
    int sum;
    printf("數字1是: ");
    scanf("%d", &integer1);
    printf("數字2是: ");
    scanf("%d", &integer2);
    sum = integer1 + integer2;
    printf("總和是 %d。\n爽了嗎?", sum);
    return 0;
}