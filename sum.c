#include <stdio.h>

int main(){
    long long integer, sum = 0;

    int i = 1;
    printf("����[�k�п�J 0\n");
    while(i < 50) {
        printf("�Ʀr %d �O: ", i);
        scanf("%lld", &integer);
        if (integer == 0)
            break;
        sum = sum + integer;
        i++;
    }
/*
    printf("�Ʀr1�O: ");
    scanf("%d", &integer);
    sum = sum + integer;

    printf("�Ʀr2�O: ");
    scanf("%d", &integer);
    sum = sum + integer;

    printf("�Ʀr3�O: ");
    scanf("%d", &integer);
    sum = sum + integer;
*/
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