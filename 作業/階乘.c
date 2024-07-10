# include<stdio.h>

int fact(int a){
    if (a < 1)
        return 1;
    else
        return fact(a - 1);
}

int main(){
    int num, result;
    printf("Enter a positive integer: ");
    scanf("%d", &num);
    result = fact(num);
    printf("%d! = %d", num, result);
    return 0;
}