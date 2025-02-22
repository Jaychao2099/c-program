# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# define MAX_EXPRESSION 100
# define FILENAME "Postfix_Expression_test.txt"

int priority(const char x, char *mode){
    switch (x){
        case '!': return 1;
        case '^': return 2;
        case '*': case '/': case '%': return 3;
        case '+': case '-': return 4;
        case '>': case '<': return 5;
        case '(': return mode == "isp" ? 8 : 0;
        default:
            printf("\nERROR: invalid operator\n");
            exit(1);
    }
}

_Bool isOperand(const char x){
    return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z') || (x >= '0' && x <= '9');
}

void Infix2Postfix(const char* expr){
    char *stack = calloc(strlen(expr), sizeof(char));
    char *output = calloc(strlen(expr), sizeof(char));
    if (stack == NULL || output == NULL){
        printf("ERROR: unable to allocate required memory in Infix2Postfix\n");
        exit(1);
    }
    int top = -1, output_last = 0;
    printf("Token\tStack\tTop\tPostfix\n");
    for (int i = 0; i <= strlen(expr); i++){
        if (i == strlen(expr)) while (top > -1) output[output_last++] = stack[top--];    //最後一格
        else if (isOperand(expr[i])) output[output_last++] = expr[i];       // operand 直接印
        else if (expr[i] == ' ');       // 'space' 直接跳過
        else if (expr[i] == ')'){       // ')'情況
            while (stack[top] != '('){
                if (top < 0){
                    printf("ERROR: illegal expression with '(', ')' pair\n");
                    exit(1);
                }
                output[output_last++] = stack[top--];
            }
            top--;
        }
        else {
            while (top > -1 && priority(expr[i], "icp") >= priority(stack[top], "isp"))  //比優先度 直到比不過
                output[output_last++] = stack[top--];
            stack[++top] = expr[i];     // 比不過就 push 進 stack
        }
        printf("%c\t", expr[i]);    // scanning token
        for (int i = 0; i <= top; i++) printf("%c", stack[i]);  // stack
        printf("\t%d\t", top);      // top
        printf("%s\t\n", output);   // postfix
    }
    printf("Postfix = %s\n", output);   // postfix
    free(stack);
    free(output);
}

int main(){
    char *expression = malloc((MAX_EXPRESSION + 1) * sizeof(char));
    if (expression == NULL){
        printf("ERROR: unable to allocate required memory in main\n");
        return 1;
    }

    const char* filename = FILENAME;
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        perror("Error opening file");
        printf("Tried to open file: %s\n", filename);
        free(expression);
        return 1;
    }

    printf("Enter your expression: ");
    if (fgets(expression, MAX_EXPRESSION, file) == NULL){
        perror("Error reading from file");
        free(expression);
        fclose(file);
        return 1;
    }
    printf("%s\n", expression);
    expression[strcspn(expression, "\n")] = '\0'; // 移除換行符

    Infix2Postfix(expression);

    free(expression);
    fclose(file);
    return 0;
}