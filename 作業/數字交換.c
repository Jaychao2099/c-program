# include <stdio.h>

int main(){
    int a, b;
    printf("Swap 2 numbers:\n");
    scanf("%d%d", &a, &b);
    printf("a = %d, b = %d\n", a, b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("After swap\na = %d, b = %d", a, b);
    return 0;
}