#include <stdio.h>

int main(){
    long int num;
    printf("Number = ");
    scanf("%d", &num);
    int isprime = 1;
    for (long int i = 2; i < num && isprime == 1; i++){
        if (num % i == 0) {
            isprime = 0;
            printf("%ld is a Composite number", num);
            break;
        }
    }
    if (isprime == 1) printf("%ld is a Prime number", num);
    return 0;
}