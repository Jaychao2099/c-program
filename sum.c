#include <stdio.h>

int main(){
    long long int integer, sum = 0;

    printf("计1琌: ");
    scanf("%lld", &integer);
    sum = sum + integer;

    printf("计2琌: ");
    scanf("%lld", &integer);
    sum = sum + integer;

    printf("计3琌: ");
    scanf("%lld", &integer);
    sum = sum + integer;
    
    printf("羆㎝琌 %lld\n瞡盾?", sum);
    return 0;
}

/*
int main(){
    double num1, num2, sum;
    printf("计1琌: ");
    scanf("%lf", &num1);
    printf("计2琌: ");
    scanf("%lf", &num2);
    sum = num1 + num2;
    printf("羆㎝琌 %lf\n瞡盾?????", sum);
    return 0;
}
*/