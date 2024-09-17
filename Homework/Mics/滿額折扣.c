# include <stdio.h>

int main() {
    int people, sum;
    printf("Please enter the nummber of customers in the table: ");
    scanf("%d", &people);
    sum = 300 * people;
    if (sum >= 3000) {
        sum = sum * 0.8;
    }
    printf("Total: %d dollars.", sum);
    return 0;
}