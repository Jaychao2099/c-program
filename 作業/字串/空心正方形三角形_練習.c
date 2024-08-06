# include <stdio.h>

int main(){
    int num;
    printf("Number = ");
    if (scanf("%d", &num) != 1 || num < 1) {
        printf("Invalid input. Please enter a integer greater than 0.\n");
        return 1;
    }

    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            if (i == 0 || i == num-1 || j == 0 || j == num-1){
                printf("*");
            } else printf(" ");
        }
        printf("\n");
    }

    for (int i = 1; i <= num; i++){
        printf("%*s", num-i, "");
        for (int j = 1; j <= 2*i-1; j++){
            if (i == 1 || i == num || j == 1 || j == 2*i-1){
                printf("*");
            } else printf(" ");
        }
        printf("\n");
    }

    return 0;
}