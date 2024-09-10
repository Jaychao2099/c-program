# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAX_INPUT 500
# define MAX_SEARCH 100

int *failure_function(char *string, int length){
    int *index = malloc(length * sizeof(int));  // failure index
    if (index == NULL){
        printf("Error allocating memory for index in failure_function\n");
        return NULL;
    }
    index[0] = 0;
    int k = 0;
    for (int i = 1; i < length; i++){
        if (k > 0 && string[k] != string[i]) k = 0;
        else if (string[k] == string[i]) k++;
        index[i] = k;
    }
    return index;
}

int KMP(char *main_str, char*search_str, int *index){
    int location;
    return location;
}

int main(){
    char *input_str = malloc(MAX_INPUT * sizeof(char));     //待搜尋的字串 放這
    if (input_str == NULL){
        printf("Error allocating memory for input_str\n");
        return 1;
    }   
    char *line = malloc(MAX_SEARCH * sizeof(char));     // 讀取檔案後 主字串 放這
    if (line == NULL){
        printf("Error allocating memory for line\n");
        free(input_str);
        return 1;
    }

    printf("Enter the string you want to search:\n");
    if (fgets(input_str, MAX_INPUT, stdin) == NULL){
        printf("Error reading input string.\n");
        free(input_str);
        free(line);
        return 1;
    }
    input_str[strcspn(input_str, "\n")] = '\0'; // 移除換行符

    FILE *file = fopen("Pi_10k.txt", "r");    // 打開文件
    if (file == NULL){
        printf("ERROR opening the file\n");
        free(input_str);
        free(line);
        return 1;
    }
    if (fgets(line, MAX_SEARCH, file) == NULL){     // 從文件中讀取主字串
        printf("Error reading main string.\n");     // 預期長度很長超過max 就不縮小記憶體空間了
        free(input_str);
        free(line);
        fclose(file);
        return 1;
    }

    int *fail_index = failure_function(input_str, strlen(input_str));     // 取得 failure array
    if (fail_index == NULL){
        printf("ERROR in failure_function");
        free(input_str);
        free(line);
        fclose(file);
        return 1;
    }
    printf("failure index: ");
    for (int i = 0; i < strlen(input_str); i++)
        printf("%d ", fail_index[i]);
    printf("\n");
    
    int result = KMP(line, input_str, fail_index);
    printf("Found at index: %d\n", result);

    // 查找子字串並計算其起始位置
    // char *pos = strstr(line, input_str);
    // if (pos != NULL){
    //     int result = pos - line; // 計算子字串起始位置的偏移量
    //     printf("Found at index: %d\n", result);
    // } else printf("String not found.\n");

    free(input_str);
    free(fail_index);
    free(line);
    fclose(file);   // 關閉文件
    
    return 0;
}