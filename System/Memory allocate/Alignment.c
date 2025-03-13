#include <stdlib.h>
#include <stdio.h>
/*
參考 https://gcc.gnu.org/onlinedocs/gcc-5.4.0/gcc/Structure-Packing-Pragmas.html

#pragma pack(n)
    將結構體的對齊設為 n 位元組（n 通常是 1、2、4、8 等）。
    例如：#pragma pack(1) 表示緊密打包，無填充；#pragma pack(4) 表示按 4 位元組對齊。
    影響範圍：從該指令開始，直到遇到另一個 #pragma pack 或檔案結束。

#pragma pack()
    沒有參數時，恢復編譯器的預設對齊規則。

#pragma pack(push, n)
    將當前的對齊狀態壓入堆疊，並將對齊設為 n 位元組。
    用途：允許臨時改變對齊，且之後可以恢復。

#pragma pack(pop)
    恢復之前壓入堆疊的對齊狀態。
    與 push 配對使用，適合局部調整結構體對齊。
*/

// 緊密打包節省空間，但可能降低 CPU 存取未對齊資料的效率。
#pragma pack(push, 1)   // 1 byte alignment
typedef struct{
    char c[3];      // 3 bytes
    int num[256];   // 1024 bytes
} test1;
#pragma pack(pop)       // restore default alignment

// 寬鬆打包增加空間，但提高 CPU 存取未對齊資料的效率。
typedef struct{
    char c[3];      // 3 bytes
    int num[256];   // 1024 bytes
} test2;



void main(){
    test1 *struc1 = (test1 *)malloc(sizeof(test1));
    test2 *struc2 = (test2 *)malloc(sizeof(test2));;
    
    printf("struc1 size: %d\n", sizeof(test1));
    printf("struc2 size: %d\n", sizeof(test2));

    free(struc1);
    free(struc2);
}
