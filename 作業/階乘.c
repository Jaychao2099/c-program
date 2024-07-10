# include<stdio.h>

long long fact(int a){
    if (a < 1)
        return 1;
    else
        return a * fact(a - 1);
}

int main(){
    int num;
    long long result;
    printf("Enter a positive integer: ");
    scanf("%d", &num);
    if (num < 1){
        printf("Plz factorial a FUCKING POSITIVE integer!\n");
        return 1;
    }
    result = fact(num);
    printf("%d! = %lld", num, result);
    return 0;
}