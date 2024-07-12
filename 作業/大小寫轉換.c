# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# define MAX_LENGTH 50

/*
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
*/

int main(){
    char input_string[MAX_LENGTH], *output_string;
    int op;
    printf("Sentence within %d words:\n", MAX_LENGTH);
    scanf("%s", &input_string);
    printf("1. All upper / 2. All lower / 3. Switch: ");
    scanf("%d", &op);

    size_t length = strlen(input_string);
    output_string = malloc((length+1) * sizeof(char));

    switch (op)
    {
    case 1:
        for(size_t i = 0; i < length; i++){
            output_string[i] = toupper(input_string[i]);
        }
        break;
    case 2:
        for(size_t i = 0; i < length; i++){
            output_string[i] = tolower(input_string[i]);
        }
        break;
    case 3:
        for(size_t i = 0; i < length; i++){
            output_string[i] = isupper(output_string[i]) ? tolower(input_string[i]) : toupper(input_string[i]);
        }
        break;
    
    default: printf("something wrong!");
        break;
    }

    printf("%s", output_string);

    free(output_string);
    
    return 0;
}