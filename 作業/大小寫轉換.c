# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# define MAX_LENGTH 500

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
    char input_string[MAX_LENGTH + 1], *output_string;
    int op;
    
    printf("Sentence within %d words:\n", MAX_LENGTH);

    if (fgets(input_string, MAX_LENGTH, stdin) == NULL) {
        printf("Error reading input string.\n");
        return 1;
    }
    input_string[strcspn(input_string, "\n")] = 0; // 移除換行符

    printf("1. All upper / 2. All lower / 3. Switch:\n");
    if (scanf("%d", &op) != 1) {
        printf("Error reading operation choice.\n");
        return 1;
    }

    size_t length = strlen(input_string);
    output_string = malloc((length+1) * sizeof(char));
    if (output_string == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    switch (op){
    case 1:
        for(size_t i = 0; i < length; i++){
            if (isalpha(input_string[i])){
                output_string[i] = toupper(input_string[i]);
            }
            else output_string[i] = input_string[i];
        }
        break;
    case 2:
        for(size_t i = 0; i < length; i++){
            if (isalpha(input_string[i])){
                output_string[i] = tolower(input_string[i]);
            }
            else output_string[i] = input_string[i];
        }
        break;
    case 3:
        for(size_t i = 0; i < length; i++){
            if (isalpha(input_string[i])){
                output_string[i] = islower(input_string[i]) ? toupper(input_string[i]) : tolower(input_string[i]);
            }
            else output_string[i] = input_string[i];
        }
        break;
    
    default:
        printf("Invalid operation choice.\n");
        free(output_string);
        return 1;
    }

    output_string[length] = '\0'; // 添加字符串結束符
    printf("%s\n", output_string);

    free(output_string);
    
    return 0;
}