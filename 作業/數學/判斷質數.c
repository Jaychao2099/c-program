#include <stdio.h>

int main(){
    long int num;
    printf("Number = ");
    scanf("%d", &num);
    int isprime = 1;
    for (long int i = 2; i <= num / i; i++){
        if (num % i == 0) {
            isprime = 0;
            printf("%ld is a Composite number, min factor is %d", num, i);
            break;
        }
    }
    if (isprime == 1) printf("%ld is a Prime number", num);
    return 0;
}