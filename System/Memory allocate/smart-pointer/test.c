#include <stdio.h>
#include "autofree.h"

typedef struct {
    int a;
    int b;
} MyStruct;

int main() {
    autofree int *num = malloc(sizeof(int));
    autofree char *msg = malloc(100);
    autofree MyStruct *obj = malloc(sizeof(MyStruct));

    if (!num || !msg || !obj) {
        fprintf(stderr, "malloc failed!\n");
        return 1;
    }

    *num = 42;
    sprintf(msg, "Hello autofree!");
    obj->a = 1;
    obj->b = 2;

    printf("num = %d\n", *num);
    printf("msg = %s\n", msg);
    printf("obj = {%d, %d}\n", obj->a, obj->b);

    return 0;
}

/*
 * gcc -g test.c -o test -Wall
 * valgrind --leak-check=full ./test
*/