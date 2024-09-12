#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1000000
#define MAX_FILENAME 256

typedef struct letter_set{
    char *name;
    char *charlist;
}letter_set;

char *choose_set(void){
    int total_sets = 3;     //增加 set 時修改
    letter_set *sets = malloc(total_sets * sizeof(letter_set));
    if (sets == NULL){
        printf("Error allocating memory for sets\n");
        exit(1);
    }
    sets[0].name = "LETTER"; sets[0].charlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    sets[1].name = "DNA"; sets[1].charlist = "ATGC";
    sets[2].name = "RNA"; sets[2].charlist = "AUGC";

    printf("Choose a letter set: ");
    for (int i = 0; i < total_sets; i++) printf("%d. %s ", i + 1, sets[i].name);
    int i = 1;
    printf("("); while (i < total_sets) printf("%d/", i++); printf("%d): ", i);
    int set_num;
    do {
        scanf("%d", &set_num);
        if (set_num < 1 || set_num > total_sets) printf("ERROR: invalid number. Choose again: ");
        else break;
    } while (1);
    return sets[set_num].charlist;
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
    char random_string[MAX_LENGTH + 1];
    char filename[MAX_FILENAME];
    int length;
    char overwrite_choice;

    // 初始化隨機數生成器
    srand(time(NULL));

    char *charset = choose_set();

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