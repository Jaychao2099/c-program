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

    printf("�`�M�O %lld�C\n�n�F��?", sum);
    return 0;
}