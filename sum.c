#include <stdio.h>

int main()
{   long long int integer, sum;

    printf("數字1是: ");
    scanf("%lld", &integer);
    sum = sum + integer;

    printf("數字2是: ");
    scanf("%lld", &integer);
    sum = sum + integer;
    
    printf("總和是 %lld。\n爽了嗎?", sum);
    return 0;
}

/*
int main(){
    double num1, num2, sum;
    printf("數字1是: ");
    scanf("%lf", &num1);
    printf("數字2是: ");
    scanf("%lf", &num2);
    sum = num1 + num2;
    printf("總和是 %lf。\n爽了嗎?????", sum);
    return 0;
}
*/