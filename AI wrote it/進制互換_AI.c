#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char* switch_base(int old, int new) {
    char input[33];
    long long dex = 0;
    char* answer;
    int max_length;

    const char num_str[] = "0123456789ABCDEF";

    printf("Number: ");
    scanf("%32s", input);
    size_t input_length = strlen(input);

    for (size_t i = 0; i < input_length; i++) {
        char* pos = strchr(num_str, toupper(input[i]));
        if (pos == NULL || (pos - num_str) >= old) {
            printf("Invalid input for base %d\n", old);
            return NULL;
        }
        dex = dex * old + (pos - num_str);
    }

    max_length = (int)(log(dex) / log(new)) + 2;
    answer = (char*)malloc(max_length * sizeof(char));
    if (answer == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int index = max_length - 1;
    answer[index--] = '\0';

    if (dex == 0) {
        answer[index] = '0';
    } else {
        while (dex > 0) {
            answer[index--] = num_str[dex % new];
            dex /= new;
        }
    }

    return answer + index + 1;
}

int main() {
    int base_old, base_new;
    char* result;

    printf("Original base: ");
    scanf("%d", &base_old);
    printf("New base: ");
    scanf("%d", &base_new);

    if (base_old < 2 || base_new < 2 || base_old > 16 || base_new > 16) {
        printf("Base must be between 2 and 16\n");
        return 1;
    }

    result = switch_base(base_old, base_new);
    if (result != NULL) {
        printf("Answer: %s\n", result);
        free(result - 1);  // 調整指針以正確釋放記憶體
    }

    return 0;
}