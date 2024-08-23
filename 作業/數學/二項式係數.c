# include <stdio.h>

int bin_recursive(int a, int b){
    if (a < 0 || b < 0){
        printf("Error: numbers must >= 1");
        return 1;
    }
    if (b == 0 || a == b) return 1;
    else return bin_recursive(a - 1, b) + bin_recursive(a - 1, b - 1);
}

int bin_math(int m, int n){
    if (n < 0){
        printf("Error: 2nd number must >= 1");
        return 1;
    }
    if (n == 0) return n;
    else {
        int result = 1;
        for(int i = 0; i < n; i++){
            result *= m - i;
            result /= i + 1;    // 階乘, 分開除
        }
        return result;
    }
}

int main(){
    int num1, num2;
    int result;
    printf("Enter two positive integer: ");
    if (scanf("%d", &num1) != 1 || scanf("%d", &num2) != 1){
        printf("Error\n");
        return 1;
    }
    
    //result = bin_recursive(num1, num2);
    result = bin_math(num1, num2);

    printf("C(%d, %d) = %d", num1, num2, result);
    return 0;
}