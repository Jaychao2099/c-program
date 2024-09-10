# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAX_LENGTH 500

int *failure_function(char *string, int length){
    int index[length];
    return index;
}

int main(){
    char *input = malloc((MAX_LENGTH + 1) * sizeof(char));
    FILE *file;
    char line[1000]; // 讀取檔案後 主字串存在這   

    if (fgets(input, MAX_LENGTH, stdin) == NULL){
        printf("Error reading input string.\n");
        return 1;
    }
    input[strcspn(input, "\n")] = '\0'; // 移除換行符
    int input_length = strlen(input);
    input = realloc(input, input_length * sizeof(char));   // 記憶體縮小為 搜尋字串 的長度
    int *fail_index = malloc(input_length * sizeof(int));  // failure index

    fail_index = failure_function(input, input_length);

    file = fopen("Pi_10k.txt", "r");    // 打開文件
    if (file == NULL) {
        printf("ERROR: cannot open the file\n");
        free(input);
        free(fail_index);
        return 1;
    }

    free(input);
    free(fail_index);
    fclose(file);   // 關閉文件
    
    return 0;
}