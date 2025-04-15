#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum FIELD { value, other_value, yet_another_value, };  // 逗點結尾，以利程式碼產生器

struct foobar {
    int field;
    int other_field;
    int yet_another_field;
};

static void *memdup(const void *src, size_t size) {
    void *mem = malloc(size);
    return mem ? memcpy(mem, src, size) : NULL;
}

#define ALLOC_INIT(type, ...) \
    (type *)memdup((type []){ __VA_ARGS__ }, sizeof(type))    // __VA_ARGS__ 是一個可變參數巨集，表示可以傳入任意數量的參數

void print_foobar(struct foobar *f) {
    printf("field: %d\n", f->field);
    printf("other_field: %d\n", f->other_field);
    printf("yet_another_field: %d\n", f->yet_another_field);
}

int main() {
    // 使用 ALLOC_INIT 分配並初始化
    struct foobar *test = ALLOC_INIT(struct foobar, {
        .field = value,    // 使用 Designated Initializers (C99)
        .other_field = other_value,
        .yet_another_field = yet_another_value
    });

    // 檢查分配是否成功
    if (test) {
        print_foobar(test);
        free(test);    // 釋放由 ALLOC_INIT (內部 malloc) 分配的記憶體
    } else {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;    // 或其他錯誤處理
    }

    return 0;
}
