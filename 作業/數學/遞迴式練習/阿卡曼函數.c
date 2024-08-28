# include <stdio.h>

long long Ackermann(int a, int b){
    if (a == 0) return b + 1;
    else if (b == 0) return Ackermann(a - 1, 1);
    else return Ackermann(a - 1, Ackermann(a, b - 1));
}

int main(){
    int A, B;
    long long result;

    printf("Enter two numbers: ");
    scanf("%d%d", &A, &B);
    if (A < 0 || B < 0){
        printf("Error: numbers must >= 0");
        return 1;
    }

    result = Ackermann(A, B);

    printf("Ackermann(%d, %d) = %lld\n", A, B, result);

    return 0;
}