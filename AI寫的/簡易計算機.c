#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("ㄏノよ猭: %s <计1> <笲衡才> <计2>\n", argv[0]);
        return 1;
    }

    double num1 = atof(argv[1]);
    char op = argv[2][0];
    double num2 = atof(argv[3]);
    double result;

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printf("岿粇埃计ぃ箂\n");
                return 1;
            }
            result = num1 / num2;
            break;
        case '^':
            result = pow(num1, num2);
            break;
        case '%':
            result = (int)num1 % (int)num2;
            break;
        default:
            printf("ぃや笲衡才\n");
            return 1;
    }

    printf("---------\n");
    printf("挡狦: %lf\n", result);

    printf("---------\n");
    printf("Program name: %s\n", argv[0]);
    printf("Argument count: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("Arg %d: %s\n", i, argv[i]);
    }

    return 0;
}