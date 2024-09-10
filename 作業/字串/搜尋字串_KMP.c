# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAX_INPUT 100
# define MAX_SEARCH 10000

int *failure_function(const char *string, int length){
    int *index = calloc(length, sizeof(int));  // failure index
    if (index == NULL) return NULL;
    int k = 0;
    for (int i = 1; i < length; i++){
        while (k > 0 && string[k] != string[i]) k = index[k - 1];
        if (string[k] == string[i]) k++;   //有相同 k才往上加
        index[i] = k;
    }
    return index;
}

int KMP(const char *main_str, const char *sub_str, const int *index, int main_len, int sub_len){
    int k = 0;      // matched 的字數
    int total = 0;  // 總 match 數
    printf("Found at index: ");
    for (int i = 0; i < main_len; i++){
        while (k > 0 && sub_str[k] != main_str[i]) k = index[k - 1];
        if (sub_str[k] == main_str[i]) k++;
        if (k == sub_len){
            printf("%d ", i - sub_len + 1);
            k = index[k - 1];
            total++;
        }
    }
    printf("\n");
    return total;
}

int main(){
    char *input_str = malloc((MAX_INPUT + 1) * sizeof(char));     //待搜尋的字串 放這
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

    printf("Enter the string you want to search (< %d letters):\n", MAX_INPUT);
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

    int sub_str = strlen(input_str);
    int main_str = strlen(line);

    int *failure_index = failure_function(input_str, sub_str);     // 取得 failure array
    if (failure_index == NULL){
        printf("Error allocating memory for failure_index in failure_function\n");
        free(input_str);
        free(line);
        fclose(file);
        return 1;
    }
    printf("failure index: ");
    for (int i = 0; i < sub_str; i++) printf("%d ", failure_index[i]);
    printf("\n");

    int result = KMP(line, input_str, failure_index, main_str, sub_str);
    printf("Total matched: %d\n", result);

    free(input_str);
    free(failure_index);
    free(line);
    fclose(file);   // 關閉文件
    
    return 0;
}