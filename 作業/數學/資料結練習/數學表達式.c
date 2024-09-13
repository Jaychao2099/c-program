# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# define MAX_EXPRESSION 100

int priority(const char x, char *mode){
    switch (x){
        case '!':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case '%':
            return 2;
        case '-':
            return 3;
        case '+':
            return 3;
        case '(':
            return mode == "isp" ? 8 : 0;
        default:
            printf("\nERROR: invalid operator\n");
            exit(1);
    }
}

_Bool isOperand(const char x){
    if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z')) return true;
    else return false;
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
        if (i == strlen(expr)) while (top > -1) output[output_last++] = stack[top--];    //�̫�@��
        else if (isOperand(expr[i])) output[output_last++] = expr[i];       // operator �����L
        else if (expr[i] == ')'){                                           // ')'���p
            while (stack[top] != '('){
                if (top < 0){
                    printf("ERROR: illegal expression with '(', ')' pair\n");
                    exit(1);
                }
                output[output_last++] = stack[top--];
            }
            top--;
        }
        else if (top > -1 && priority(expr[i], "icp") >= priority(stack[top], "isp")){  //���u����
            output[output_last++] = stack[top];
            stack[top] = expr[i];
        }
        else {          // �񤣹L�N push �i stack
            top++;
            stack[top] = expr[i];
        }
        printf("%c\t", expr[i]);    //scanning
        for (int i = 0; i <= top; i++) printf("%c", stack[i]);
        printf("\t%d\t", top);
        printf("%s\t\n", output);
    }
}

int main(){
    char *expression = malloc((MAX_EXPRESSION + 1) * sizeof(char));
    if (expression == NULL){
        printf("ERROR: unable to allocate required memory in main\n");
        return 1;
    }

    const char* filename = "�ƾǪ�F��_test.txt";
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
    expression[strcspn(expression, "\n")] = '\0'; // ���������

    Infix2Postfix(expression);

    free(expression);
    fclose(file);
    return 0;
}