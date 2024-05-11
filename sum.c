#include <stdio.h>
/*
int main()
{   long long int integer1;
    long long int integer2;
    long long int sum;
    printf("计1琌: ");
    scanf("%lld", &integer1);
    printf("计2琌: ");
    scanf("%lld", &integer2);
    sum = integer1 + integer2;
    printf("羆㎝琌 %lld\n瞡盾?", sum);
    return 0;
}
*/
int main()
{   long double num1;
    long double num2;
    long double sum;
    printf("计1琌: ");
    scanf("%Lf", &num1);
    printf("计2琌: ");
    scanf("%Lf", &num2);
    sum = num1 + num2;
    printf("羆㎝琌 %Lf\n瞡盾?", sum);
    return 0;
}