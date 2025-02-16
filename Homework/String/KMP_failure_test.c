# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAX_INPUT 100

int *failure_function(const char *string, int length){
    int *index = calloc(length, sizeof(int));  // failure index
    if (index == NULL) return NULL;

    int k = 0;
    for (int i = 1; i < length; i++){
        while (k > 0 && string[k] != string[i])
            k = index[k - 1];   // 有不同 k往前找
        if (string[k] == string[i])
            k++;   //有相同 k才往上加
        index[i] = k;
    }

    return index;
}

int main(){
    char *input_str = malloc((MAX_INPUT + 1) * sizeof(char));     //待搜尋的字串 放這 

    printf("Enter the string you want to search (< %d letters):\n", MAX_INPUT);
    if (fgets(input_str, MAX_INPUT, stdin) == NULL){
        printf("Error reading input string.\n");
        free(input_str);
        return 1;
    }
    input_str[strcspn(input_str, "\n")] = '\0'; // 移除換行符

    int sub_str = strlen(input_str);

    int *failure_index = failure_function(input_str, sub_str);     // 取得 failure array

    printf("failure index: ");
    for (int i = 0; i < sub_str; i++) printf("%d ", failure_index[i]);
    printf("\n");
    
    return 0;
}