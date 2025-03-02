#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void swap(char *a, char *b){
    *a = *a ^ *b; *b = *a ^ *b; *a = *a ^ *b;
}

// 交換字元，O(n) + O(n/2) = O(n)
char *reverse_iter(char *s){
    int last = strlen(s) - 1;
    for (int i = 0; i < last; i++, last--){
        swap(s + i, s + last);
    }
    return s;
}

// 首尾互換 + 尾與'\0'互換，O(n^2)
char *reverse_rec(char *s){
    if ((*s == '\0') || (*(s + 1) == '\0')) return NULL;
        
    reverse_rec(s + 1);
    swap(s, (s + 1));
    
    if (*(s + 2) != '\0') reverse_rec(s + 2);
    reverse_rec(s + 1);
}

// 計算字串長度時，即可交換字元，O(n)
int rev_core(char *head, int idx){
    if (head[idx] != '\0') {
        int end = rev_core(head, idx + 1);
        if (idx > end / 2)
            swap(head + idx, head + end - idx);
        return end;
    }
    return idx - 1;
}

char *reverse_rec_opt(char *s){
    rev_core(s, 0); 
    return s;
}

int main(){
    char *str = "abcdefg";  // read-only
    char *str1 = memcpy(malloc(strlen(str) + 1), str, strlen(str) + 1);
    char *str2 = memcpy(malloc(strlen(str) + 1), str, strlen(str) + 1);
    char *str3 = memcpy(malloc(strlen(str) + 1), str, strlen(str) + 1);

    printf("%s\n", reverse_iter(str1));

    reverse_iter(str2);
    printf("%s\n", str2);
    
    printf("%s\n", reverse_rec_opt(str3));

    return 0;
}