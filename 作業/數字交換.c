# include <stdio.h>

int main(){
    int a, b;
    printf("Enter 2 numbers to swap:\n");
    scanf("%d%d", &a, &b);
    printf("a = %d, b = %d\n", a, b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("After swap\na = %d, b = %d\n", a, b);
    return 0;
}