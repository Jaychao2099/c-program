#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

int32_t abs_no_branch(int32_t x) {
    int32_t sign = x >> 31;     // 獲取符號位：x>=0時為0(所有位都是0)，x<0時為-1(所有位都是1) (算術位移)
    return (x ^ sign) - sign;   // 若 sign == 0 (正數)，x 不變；若 sign == -1 (負數)，x 取補數後減-1 (== 加1)
}

bool is_2s_power(int x) {
    return (x > 0) && ((x & (x - 1)) == 0); // 判斷 x 是否為正數且只有一個位元為1
}

char big2small(char x) {
    return x | ' ';     // x 為大寫 --> x +=32； x 為小寫 --> x 不變
}

// 僅限字母，其他字元可能會出錯
char small2big(char x) {
    return x & ~' ';     // x 為小寫 --> x -=32； x 為大寫 --> x 不變
}

// 僅限字母，其他字元可能會出錯
char small_big_exchange(char x) {
    return x ^ ' ';     // x 為小寫 --> x -=32； x 為大寫 --> x +=32；
}

bool is_letter(char x) {
    return ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'));
}

/*
* 用加法器來思考: x & y 是進位, x ^ y 是位元和, >> 1 是向右移一位
* 位元相加不進位的總和: x ^ y; 位元相加產生的進位值: (x & y) << 1
* x + y = x ^ y + ( x & y ) << 1
* 所以 (x + y) / 2
* = (x + y) >> 1
* = (x ^ y + (x & y) << 1) >> 1
* = (x & y) + ((x ^ y) >> 1)
*/
// 避免 (x + y) overflow (對 binary search 重要)
int32_t two_nums_avg(int32_t x, int32_t y){
    return (x & y) + ((x ^ y) >> 1);    
}

// 需 INT_MIN <= (x - y) <= INT_MAX
int32_t max(int32_t x, int32_t y) {
    int32_t diff = x - y;               // 計算 x - y 的差值
    return -(diff & (diff >> 31)) + x;   // 如果 diff 為負數，則返回 -(diff) + x = y；如果 diff 為正數，則返回 (0...0) + x = x
}

// 需 INT_MIN <= (x - y) <= INT_MAX
int32_t min(int32_t x, int32_t y) {
    int32_t diff = x - y;               // 計算 x - y 的差值
    return (diff & (diff >> 31)) + y;   // 如果 diff 為負數，則返回 (diff) + y = x；如果 diff 為正數，則返回 (0...0) + y = y
}

// 使用 XOR 交換兩個數的值，不用管資料型態 (但占用的位元數要相同)
#define xor_swap(x, y) do { \
    if ((x) != (y)) {       \
        *(x) ^= *(y);       \
        *(y) ^= *(x);       \
        *(x) ^= *(y);       \
    }                       \
} while (0)

// 檢測 null terminator
#if LONG_MAX == 2147483647L
#define DETECTNULL(X) \
    (((X) - 0x01010101) & ~(X) & 0x80808080)
#else
#if LONG_MAX == 9223372036854775807L
#define DETECT(X) \
    (((X) - 0x0101010101010101) & ~(X) & 0x8080808080808080)
#else
#error long int is not a 32bit or 64bit type.
#endif
#endif

// 用 word-wise 檢測字串的長度，直到遇到 null terminator 為止，並返回字串的長度 (不含 null terminator)
unsigned int strlen_detect(const char *s) {
    const char *p = s;

    // 1. 處理開頭未對齊的 bytes (位址的尾數有1)
    while (((long)p & (sizeof(unsigned long) - 1))) {
        if (!*p)
            return p - s;
        p++;
    }
    
    // 2. word‐wise 偵測
    unsigned long *lp = (unsigned long *)p;
    while (!DETECTNULL(*lp)) {
        lp++;
    }
    
    // 3. 逐 byte 檢查這個 word，確定真正的 '\0' 位置
    p = (const char *)lp;
    while (*p) p++;

    return (unsigned int)(p - s);
}

// 獲取各個 byte 的值
unsigned char lowest_byte(int32_t val){
    return val & 0xff;
}
unsigned char low_byte(int32_t val){
    return (val >> 8) & 0xff;
}
unsigned char high_byte(int32_t val){
    return (val >> 16) & 0xff;
}
unsigned char highest_byte(int32_t val){
    return (val >> 24) & 0xff;
}

// 獲取符號位
bool sign_bit(int32_t val){
    return val & 0x80000000;
}

int main(){
    char *str = "You are GOOD!";

    for (int i = 0; i < strlen_detect(str); i++) {
        printf("%c", str[i]);
    }
    printf(" = %d character\n", strlen_detect(str));

    printf("Big case = ");
    for (int i = 0; i < strlen_detect(str); i++) {
        printf("%c", is_letter(str[i]) ? small2big(str[i]) : str[i]);
    }
    printf("\n");

    printf("Small case = ");
    for (int i = 0; i < strlen_detect(str); i++) {
        printf("%c", is_letter(str[i]) ? big2small(str[i]) : str[i]);
    }
    printf("\n");

    printf("Exchange case = ");
    for (int i = 0; i < strlen_detect(str); i++) {
        printf("%c", is_letter(str[i]) ? small_big_exchange(str[i]) : str[i]);
    }
    printf("\n");

    int x = INT32_MIN / 2;  // -1073741824
    int y = INT32_MAX / 2;  //  1073741823

    printf("abs_no_branch(%d) = %d\n", x, abs_no_branch(x));

    printf("is_2s_power(%d) = %d\n", x, is_2s_power(x));

    printf("two_nums_avg(%d, %d) = %d\n", x, y, two_nums_avg(x, y));

    printf("max of %d and %d = %d\n", x, y, max(x, y));
    printf("min of %d and %d = %d\n", x, y, min(x, y));
    
    printf("xor_swap(%d, %d) = ", x, y);
    xor_swap(&x, &y);
    printf("(%d, %d)\n", x, y);
    
    printf("lowest_byte(%d) = 0x%x\n", x, lowest_byte(x));
    printf("low_byte(%d) = 0x%x\n", x, low_byte(x));
    printf("high_byte(%d) = 0x%x\n", x, high_byte(x));
    printf("highest_byte(%d) = 0x%x\n", x, highest_byte(x));
    
    printf("sign_bit(%d) = %d\n", x, sign_bit(x));
    printf("sign_bit(%d) = %d\n", y, sign_bit(y));

    return 0;
}