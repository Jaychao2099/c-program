#include <stdio.h>
/*
int main()
{   long long int integer1;
    long long int integer2;
    long long int sum;
    printf("�Ʀr1�O: ");
    scanf("%lld", &integer1);
    printf("�Ʀr2�O: ");
    scanf("%lld", &integer2);
    sum = integer1 + integer2;
    printf("�`�M�O %lld�C\n�n�F��?", sum);
    return 0;
}
*/
int main()
{   long double num1;
    long double num2;
    long double sum;
    printf("�Ʀr1�O: ");
    scanf("%Lf", &num1);
    printf("�Ʀr2�O: ");
    scanf("%Lf", &num2);
    sum = num1 + num2;
    printf("�`�M�O %Lf�C\n�n�F��?", sum);
    return 0;
}