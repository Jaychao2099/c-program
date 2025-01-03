#include <stdio.h>

int exp_1(int x, int n){
    if (n == 0) return 1;
    if (n == 1) return x;
    int temp = exp_1(x, n / 2);
    if (n % 2) return temp * temp * x;
    return temp * temp;
}

int exp_2(int x, int n){
    int result = 1;
    while (n){
        if (n % 2) result *= x;
        x *= x;
        n /= 2;
    }
    return result;
}

int exp_3(int x, int n){
    int temp = 1;
    if (n % 2) temp = x;
    else temp = 1;
    if (n < 2) return temp;
    return temp * exp_3(x * x, n / 2);
}

int main(){
    int x, n;
    printf("Enter base and exponent: ");
    scanf("%d%d", &x, &n);
    printf("%d^%d = %d\n", x, n, exp_1(x, n));
    printf("%d^%d = %d\n", x, n, exp_2(x, n));
    printf("%d^%d = %d\n", x, n, exp_3(x, n));
    return 0;
}
