#include <stdio.h>

int main(){
    printf("short int: %d\n", sizeof(short int));

    printf("int: %d\n", sizeof(int));

    printf("unsigned int: %d\n", sizeof(unsigned int));

    printf("long int: %d\n", sizeof(long int));
    
    printf("long long int: %d\n", sizeof(long long int));
    
    printf("char: %d\n", sizeof(char));
    
    printf("float: %d\n", sizeof(float));
    
    printf("double: %d\n", sizeof(double));

    printf("long double: %d\n", sizeof(long double));

    printf("void: %d\n", sizeof(void));
    
    return 0;
}