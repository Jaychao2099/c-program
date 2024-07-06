#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Program name: %s\n", argv[0]);
    printf("Argument count: %d\n", argc);
    for (int i = 1; i <= argc; i++) {
        printf("Arg %d: %s\n", i, argv[i]);
    }
    return 0;
}