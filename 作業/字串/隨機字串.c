#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_LENGTH 1000000
#define MAX_FILENAME 256
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct letter_set{
    const char *name;
    const char *charlist;
}letter_set;

const char *choose_set(void){
    const letter_set sets[] = {
        {"LETTER", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"},
        {"DNA", "ATGC"},
        {"RNA", "AUGC"},
    };

    printf("Choose a letter set: ");
    for (int i = 0; i < ARRAY_SIZE(sets); i++) printf("%d. %s ", i + 1, sets[i].name);
    int i = 1;
    printf("("); while (i < ARRAY_SIZE(sets)) printf("%d/", i++); printf("%d): ", i);
    int set_num;
    do {
        if (scanf("%d", &set_num) != 1){    // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("ERROR: invalid input. Please enter a number: ");
        } else if (set_num < 1 || set_num > ARRAY_SIZE(sets)){
            printf("ERROR: invalid number. Choose again ");
            i = 1;
            printf("("); while (i < ARRAY_SIZE(sets)) printf("%d/", i++); printf("%d): ", i);
        } else break;
    } while (1);
    return sets[set_num - 1].charlist;
}

void generate_random_string(char *str, const char *charset, int length) {
    int charset_length = strlen(charset);
    for (int i = 0; i < length; i++) {
        int index = rand() % charset_length;
        str[i] = charset[index];
    }
    str[length] = '\0';
}

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

int main() {
    char *random_string;
    char filename[MAX_FILENAME];
    int length;
    char overwrite_choice;

    // 初始化隨機數生成器
    srand(time(NULL));

    // 選擇字符集
    const char *charset = choose_set();

    // 獲取用戶輸入的檔案名稱並檢查是否存在
    do {
        printf("File name: ");
        scanf("%255s", filename);

        if (file_exists(filename)) {
            printf("File '%s' already exists. Overwrite? (y/n): ", filename);
            scanf(" %c", &overwrite_choice);
            if (overwrite_choice == 'y' || overwrite_choice == 'Y') break;
        } else break;
    } while (1);

    // 格式化數字 (MAX_LENGTH 加逗點)
    setlocale(LC_ALL, "");
    
    // 獲取用戶輸入的字符串長度
    do {
        printf("String length (max %'d): ", MAX_LENGTH);
        scanf("%d", &length);
        if (length < 1 || length > MAX_LENGTH) printf("ERROR: invalid length, must be 1 ~ %'d\n", MAX_LENGTH);
        else break;
    } while (1);
    random_string= malloc((length + 1) * sizeof(char));
    if (random_string == NULL){
        printf("Error allocating memory for random_string\n");
        return 1;
    }

    // 生成隨機字符串
    generate_random_string(random_string, charset, length);

    // 將隨機字符串寫入文件
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("ERROR: cannot create or open file '%s'\n", filename);
        return 1;
    }

    fprintf(file, "%s", random_string);
    fclose(file);

    printf("Random string has been written into '%s'\n", filename);

    free(random_string);

    return 0;
}