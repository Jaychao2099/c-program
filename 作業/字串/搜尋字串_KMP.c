# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAX_INPUT 100
# define MAX_SEARCH 1000000
# define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const char *choose_file(void){
    const char *file_name[] = {
        "Pi_10k.txt",
        "DNA_1.txt",
        "RNA_1.txt",
        "Letters_1.txt"
    };
    printf("Choose a file to search:\n");
    for (int i = 0; i < ARRAY_SIZE(file_name); i++) printf("%d. %s ", i + 1, file_name[i]);
    int i = 1;
    printf("("); while (i < ARRAY_SIZE(file_name)) printf("%d/", i++); printf("%d): ", i);
    int file_num;
    do {
        if (scanf("%d", &file_num) != 1){    // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("ERROR: invalid input. Please enter a number: ");
        } else if (file_num < 1 || file_num > ARRAY_SIZE(file_name)){
            printf("ERROR: invalid number. Choose again ");
            i = 1;
            printf("("); while (i < ARRAY_SIZE(file_name)) printf("%d/", i++); printf("%d): ", i);
        } else break;
    } while (1);
    setbuf(stdin, '\0');    //清空 stdin
    return file_name[file_num - 1];
}

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
    int c = 0;      // matched 的字數
    int total = 0;  // 總 match 數
    printf("Found at index: ");
    for (int i = 0; i < main_len; i++){
        while (c > 0 && sub_str[c] != main_str[i]) c = index[c - 1];
        if (sub_str[c] == main_str[i]) c++;
        if (c == sub_len){
            printf("%d ", i - sub_len + 1);
            c = index[c - 1];
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

    const char *file_name = choose_file();  //選擇文件名稱

    printf("Enter the string you want to search (< %d letters):\n", MAX_INPUT);
    if (fgets(input_str, MAX_INPUT, stdin) == NULL){
        printf("Error reading input string.\n");
        free(input_str);
        free(line);
        return 1;
    }
    input_str[strcspn(input_str, "\n")] = '\0'; // 移除換行符

    FILE *file = fopen(file_name, "r");    // 打開文件
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