#include <stdio.h>

float polya(float n, float x);

int main() {
    float n, x;
    
    // 取得使用者輸入
    printf("Enter the value of n: ");
    scanf("%f", &n);
    printf("Enter the value of x: ");
    scanf("%f", &x);
    
    // 呼叫 polya 函式並印出結果
    printf("The value of the polynomial is: %f\n", polya(n, x));
    
    return 0;
}

float polya(float n, float x) {
    if (n == 0) 
        return 1.0;
    if (n == 1)
        return x;
    else {
        float result_0, result_1, change = 1., x;
        for(int i = 2; i <= n; i++){
            change = result_1;
            result_1 = ((2.*i-1.)*x*result_1 - (i-1)*result_0)/i;
            result_0 = change;
        }
        return result_1;
    }
}
