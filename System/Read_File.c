#include <stdio.h>

// 注意事項
// 確保文件 "input.txt" 存在於執行程序的同一目錄下，或者提供文件的完整路徑。
// 檢查 fopen 是否返回 NULL，以確保文件成功打開。
// 使用 fclose 關閉文件以避免內存泄漏。

int main() {
    FILE *file;
    char line[256];

    // 打開文件
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("ERROR: cannot open the file\n");
        return 1;
    }

    // 逐行讀取文件並顯示內容
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    // 關閉文件
    fclose(file);
    return 0;
}
