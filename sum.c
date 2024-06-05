#include <stdio.h>

int main(){
    long long integer, sum = 0;

    int i = 1;
    printf("氨ゎ猭叫块 0\n");
    while(i < 50) {
        printf("计 %d 琌: ", i);
        scanf("%lld", &integer);
        if (integer == 0)
            break;
        sum = sum + integer;
        i++;
    }
/*
    printf("计1琌: ");
    scanf("%d", &integer);
    sum = sum + integer;

    printf("计2琌: ");
    scanf("%d", &integer);
    sum = sum + integer;

    printf("计3琌: ");
    scanf("%d", &integer);
    sum = sum + integer;
*/
    printf("羆㎝琌 %lld\n瞡盾?", sum);
    return 0;
}

/*
int main(){
    double num1, num2, sum;
    printf("计1琌: ");
    scanf("%lf", &num1);
    printf("计2琌: ");
    scanf("%lf", &num2);
    sum = num1 + num2;
    printf("羆㎝琌 %lf\n瞡盾?????", sum);
    return 0;
}
*/