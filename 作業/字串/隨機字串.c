#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1000000
#define MAX_FILENAME 256
#define STR_LETTER "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
#define STR_DNA "ATGC"
#define STR_RNA "AUGC"

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
    char charset[] = STR_RNA;
    char random_string[MAX_LENGTH + 1];
    char filename[MAX_FILENAME];
    int length;
    char overwrite_choice;

    // 初始化隨機數生成器
    srand(time(NULL));

    // 獲取用戶輸入的檔案名稱並檢查是否存在
    do {
        printf("File name: ");
        scanf("%255s", filename);

        if (file_exists(filename)) {
            printf("File '%s' already exists. Overwrite? (y/n): ", filename);
            scanf(" %c", &overwrite_choice);
            if (overwrite_choice == 'y' || overwrite_choice == 'Y') {
                break;
            }
        } else {
            break;
        }
    } while (1);

    // 獲取用戶輸入的字符串長度
    printf("String length (max %d): ", MAX_LENGTH);
    scanf("%d", &length);

    if (length <= 0 || length > MAX_LENGTH) {
        printf("ERROR: invalid length, must be 1 ~ %d\n", MAX_LENGTH);
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

    return 0;
}