# include <stdio.h>
int main(){
    char input, change;

    printf("Please type a letter: ");
    scanf("%c", &input);
    if (input >= 65, input <= 90){
        change = input + 97 - 65;
        printf("The lower case is: %c", change);
    }
    else if (input >= 97, input <= 122){
        change = input + 65 - 97;
        printf("The capital is: %c", change);
    }
    else {
        printf("Please restart the exe. and type a letter, not a symbol.");
    }

    /*
    for (int i = 33; i < 128; i++){
        char input = i;
        printf("%d: %c\n", i,input);
    }
    */

    return 0;
}