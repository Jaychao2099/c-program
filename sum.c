#include <stdio.h>

int main(){
    long long int integer, sum = 0;

    printf("�Ʀr1�O: ");
    scanf("%lld", &integer);
    sum = sum + integer;

    printf("�Ʀr2�O: ");
    scanf("%lld", &integer);
    sum = sum + integer;

    printf("�Ʀr3�O: ");
    scanf("%lld", &integer);
    sum = sum + integer;
    
    printf("�`�M�O %lld�C\n�n�F��?", sum);
    return 0;
}

/*
int main(){
    double num1, num2, sum;
    printf("�Ʀr1�O: ");
    scanf("%lf", &num1);
    printf("�Ʀr2�O: ");
    scanf("%lf", &num2);
    sum = num1 + num2;
    printf("�`�M�O %lf�C\n�n�F��?????", sum);
    return 0;
}
*/