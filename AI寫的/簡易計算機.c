#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("�ϥΤ�k: %s <�Ʀr1> <�B���> <�Ʀr2>\n", argv[0]);
        //return 1;
    }

    int num1 = atoi(argv[1]);
    char op = argv[2][0];
    int num2 = atoi(argv[3]);
    int result;

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
                printf("���~�G���Ƥ��ର�s\n");
                return 1;
            }
            result = num1 / num2;
            break;
        default:
            printf("��������B���\n");
            return 1;
    }

    printf("���G: %d\n", result);

    printf("---------\n");
    printf("Program name: %s\n", argv[0]);
    printf("Argument count: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("Arg %d: %s\n", i, argv[i]);
    }

    return 0;
}