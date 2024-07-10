# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

char* switch_base(int old, int new){
    char input[33];
    long long dex = 0;
    int max_length;
    char* answer;

    const char num_str[] = "0123456789ABCDEF";

    scanf("%32s", input);
    size_t input_length = strlen(input);

    for (size_t i = 0; i < input_length; i++){
        for (size_t j = 0; j < 16; j++){
            if (input[i] == num_str[j]){
                dex = dex + j * pow(old, input_length - 1 - i);
            }
        }
    }   //dex = num in base 10

    max_length = (int)(log(dex) / log(new)) + 2;

    if (dex == 0){
        answer = "0";
        return answer;
    }
    answer = (char*)malloc(max_length * sizeof(char));
    if (answer == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    max_length--;
    answer[max_length--] = '\0';

    while (dex > 0){
        answer[max_length--] = num_str[dex % new];
        dex = dex / new;
    }

    return answer + max_length + 1;
}

int main(){
    int base_old, base_new;
    char* result;
    printf("Original base: ");
    scanf("%d", &base_old);
    printf("New base: ");
    scanf("%d", &base_new);
    if (base_old < 2 || base_new < 2 || base_old > 16 || base_new > 16){
        printf("Base must between 2 ~ 16\n");
        return 1;
    }
    printf("Number: ");
    result = switch_base(base_old, base_new);
    printf("Answer: %s", result);

    free(result - 1);

    return 0;
}