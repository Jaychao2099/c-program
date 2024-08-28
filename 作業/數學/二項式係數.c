# include <stdio.h>
# include <math.h>

# define int_error 42069

int bin_recursive(int a, int b){
    if (a < 0 || b < 0){
        printf("Error: numbers must >= 0\n");
        return int_error;
    }
    if (a < b){
        printf("Error: 1st number must >= 2nd number\n");
        return int_error;
    }
    if (b == 0 || a == b) return 1;
    else return bin_recursive(a - 1, b) + bin_recursive(a - 1, b - 1);
}

int bin_math(int m, int n){
    if (n < 0){
        printf("Error: 2nd number must >= 0\n");
        return int_error;
    }
    if (m < n && m > 0){
        printf("Error: 1st number must >= 2nd number\n");
        return int_error;
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
    printf("Enter two integer: ");
    if (scanf("%d", &num1) != 1 || scanf("%d", &num2) != 1){
        printf("Error\n");
        return 1;
    }
    
    //result = bin_recursive(num1, num2);
    result = bin_math(num1, num2);

    if (result == int_error) return 1;
    else printf("C(%d, %d) = %d", num1, num2, result);
    
    return 0;
}