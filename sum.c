#include <stdio.h>

int main(){
    long long integer, sum = 0;

    int i = 1;
    printf("Enter 0 to stop the addition\n");
    while(i < 50) {
        printf("Number %d is: ", i);
        scanf("%lld", &integer);
        if (integer == 0)
            break;
        sum = sum + integer;
        i++;
    }

    printf("\nThe sum is %lld\n\nAre you happy?\n ", sum);
    return 0;
}