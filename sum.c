#include <stdio.h>

int main(){
    long long integer, sum = 0;

    int i = 1;
    printf("停止加法請輸入 0\n");
    while(i < 50) {
        printf("數字 %d 是: ", i);
        scanf("%lld", &integer);
        if (integer == 0)
            break;
        sum = sum + integer;
        i++;
    }

    printf("總和是 %lld。\n爽了嗎?", sum);
    return 0;
}