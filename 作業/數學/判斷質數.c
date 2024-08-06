#include <stdio.h>

int main(){
    long long num;
    printf("Number = ");
    if (scanf("%lld", &num) != 1 || num <= 1) {
        printf("Invalid input. Please enter a number greater than 1.\n");
        return 1;
    }

    if (num == 2) {
        printf("2 is a Prime number\n");
        return 0;
    }
    if (num % 2 == 0) {
        printf("%lld is a Composite number, min factor is 2\n", num);
        return 0;
    }

    int isprime = 1;
    for (long long i = 3; i <= num / i; i += 2){
        if (num % i == 0) {
            isprime = 0;
            printf("%lld is a Composite number, min factor is %d\n", num, i);
            break;
        }
    }
    if (isprime) printf("%lld is a Prime number\n", num);
    return 0;
}