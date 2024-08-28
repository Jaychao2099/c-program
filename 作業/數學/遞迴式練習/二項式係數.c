# include <stdio.h>
# include <math.h>

# define int_error 0

int bin_recursive(int a, int b){        //一般二項式 遞迴
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

int bin_extend_recursive(int m, int n){     //擴展二項式 遞迴
    if (n < 0) {
        printf("Error: 2nd number must >= 0\n");
        return int_error;
    }
    else if (m < n && m > 0) return int_error;
    if (n == 0) return 1;
    if (n == 1) return m;
    if (m < 0)  return ((n % 2 == 0) ? 1 : -1) * bin_extend_recursive(-m + n - 1, n); // m < 0
    return bin_extend_recursive(m - 1, n) + bin_extend_recursive(m - 1, n - 1); // m >= 0
}

int bin_extend_iterative(int m, int n){     //擴展二項式 迭代
    if (n < 0){
        printf("Error: 2nd number must >= 0\n");
        return int_error;
    }
    if (m < n && m > 0) return int_error;
    if (n == 0) return 1;
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
    
    int mode;
    printf("Choose mode:\n1. normal recursive\n2. extended recursive\n3. extended iterative\n(1/2/3): ");
    do {
        scanf("%d", &mode);
        switch (mode){
            case 1:
                result = bin_recursive(num1, num2);       //一般二項式 遞迴
                break;
            case 2:
                result = bin_extend_recursive(num1, num2);  //擴展二項式 遞迴
                break;
            case 3:
                result = bin_extend_iterative(num1, num2);  //擴展二項式 迭代
                break;
            default:
                printf("Plz choose (1/2/3): ");
                break;
        }
    } while (mode > 3 || mode < 1);

    if (result == int_error) return 1;
    else printf("C(%d, %d) = %d", num1, num2, result);
    
    return 0;
}