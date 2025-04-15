#include <stdio.h>

#define ___PASTE(a, b) a##b
#define __PASTE(a, b) ___PASTE(a, b)

#define __UNIQUE_ID(prefix) \
    __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

#define __max(t1, t2, max1, max2, x, y) ({		\
	t1 max1 = (x);					    \
	t2 max2 = (y);					    \
	(void) (&max1 == &max2);			\
	max1 > max2 ? max1 : max2; })

#define max(x, y)                                 \
    __max(typeof(x), typeof(y),                   \
          __UNIQUE_ID(max1_), __UNIQUE_ID(max2_), \
          x, y)

/*
___paste(a , b) 會將 a 和 b 兩個參數連接起來，形成一個新的標識符。
__paste(a , b) 會調用 ___paste(a , b) 來進行實際的連接操作。這樣做的目的是為了避免在巨集展開時出現重複的標識符，從而導致編譯錯誤。

__UNIQUE_ID(prefix) 會生成一個唯一的標識符，這個標識符是由 prefix 和當前的計數器值組成的。這樣可以確保每次調用 __UNIQUE_ID(prefix) 時都會生成一個不同的標識符。
__COUNTER__ 是一個 GNU extension。每次 __COUNTER__ 會得到一個流水號碼，藉由 ## 和 __COUNTER__ 的組合，就能避免變數命名的衝突。


typeof(x) _x = (x);  取值出來，避免多次計算
typeof(y) _y = (y);  取值出來，避免多次計算
(void) (&_x == &_y); 若型態不一致，編譯器就會拋出以下警告訊息:"comparison of distinct pointer types lacks a cast"及早發現並警示開發者。
*/

#define X 1
#define Y 2

int main() {
    char sym[max(X, Y)];    // 給array宣告非const的大小，可能有風險 // 參考 https://hackmd.io/@sysprog/linux-macro-minmax#%E6%9B%B4%E5%A4%9A%E7%9A%84%E6%AA%A2%E6%9F%A5
    printf("Sizeof(sym) is: %d u\n", sizeof(sym)); // 2
    return 0;                                 
}

int main() {
    int a = 5, b = 10;
    float f1 = 3.14, f2 = 2.71;
    int i = 1;

    // 基本用法
    int max_val = max(a, b); // max_val = 10
    printf("Max of %d and %d is: %d\n", a, b, max_val);

    // 浮點數用法
    float max_f = max(f1, f2); // max_f = 3.14
    printf("Max of %f and %f is: %f\n", f1, f2, max_f);

    // 避免副作用
    // 如果使用簡單的 #define max(x,y) ((x)>(y)?(x):(y))
    // 下一行會導致 i 增加兩次
    int max_i = max(i++, 5); // i++ 只會執行一次, max_i = 5, 之後 i = 2
    printf("Max of i++ and 5 is: %d, i is now: %d\n", max_i, i);

    // 類型檢查 (編譯器可能會在此處產生警告)
    int *ptr_a = &a;
    float *ptr_f1 = &f1;
    max(ptr_a, ptr_f1); // 可能觸發 "comparison of distinct pointer types lacks a cast" 警告

    return 0;
}
