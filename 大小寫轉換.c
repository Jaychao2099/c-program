# include <stdio.h>
int main(){
    char input, change;

    printf("Please type a letter: ");
    scanf("%c", &input);
    if (input >= 'A' && input <= 'Z'){
        change = input + 'a' - 'A';
        printf("The lower case is: %c", change);
    }
    else if (input >= 'a' && input <= 'z'){
        change = input + 'A' - 'a';
        printf("The capital is: %c", change);
    }
    else {
        printf("Please restart the exe. and type a letter, not a symbol.");
    }

    return 0;
}