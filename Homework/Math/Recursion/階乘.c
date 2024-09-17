# include <stdio.h>

# define int_error 42069

long long fact(int a){
    if (a < 0){
        printf("Plz factorial a fuckin' POSITIVE integer!\n");
        return int_error;
    }
    else if (a > 20){
        printf("Too big!\n");
        return int_error;
    }
    else return (a < 1) ? 1 : a * fact(a - 1);
    /*
    if (a < 1)
        return 1;
    else
        return a * fact(a - 1);
    */
}

int main(){
    int num;
    long long result;
    printf("Enter a positive integer: ");
    scanf("%d", &num);
    
    result = fact(num);

    if (result == int_error) return 1;
    else printf("%d! = %lld", num, result);

    return 0;
}