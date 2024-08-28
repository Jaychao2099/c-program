# include <stdio.h>

int GCD(int a, int b){
    if (a % b == 0) return b;
    else return GCD(b, a % b);
}

int main(){
    int A, B, result;
    printf("Enter two numbers: ");
    scanf("%d%d", &A, &B);

    result = GCD(A, B);

    printf("gcd(%d, %d) = %d\n", A, B, result);

    return 0;
}