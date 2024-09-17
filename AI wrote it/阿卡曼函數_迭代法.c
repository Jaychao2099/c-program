#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1000000

typedef struct {
    long long a;
    long long b;
} State;

long long Ackermann(long long a, long long b) {
    State* stack = (State*)malloc(STACK_SIZE * sizeof(State));
    int top = 0;

    stack[top++] = (State){a, b};

    while (top > 0) {
        State current = stack[--top];

        if (current.a == 0) {
            if (top == 0) {
                free(stack);
                return current.b + 1;
            }
            stack[top - 1].b = current.b + 1;
        } else if (current.b == 0) {
            stack[top++] = (State){current.a - 1, 1};
        } else {
            if (top + 2 > STACK_SIZE) {
                printf("Stack overflow\n");
                free(stack);
                exit(1);
            }
            stack[top++] = (State){current.a - 1, 0};  // 這個 0 將在下一次迭代中被替換
            stack[top++] = (State){current.a, current.b - 1};
        }
    }

    free(stack);
    return -1;  // 這行不應該被執行到
}

int main(){
    //int A, B;
    long long A, B, result;
    
    printf("Enter two numbers: ");
    scanf("%lld%lld", &A, &B);
    if (A < 0 || B < 0){
        printf("Error: numbers must >= 0");
        return 1;
    }

    result = Ackermann(A, B);

    printf("Ackermann(%lld, %lld) = %lld\n", A, B, result);

    return 0;
}