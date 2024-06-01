#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){
    char *data_types[] = {
        "short int", 
        "int", 
        "unsigned int", 
        "unsigned octal int", 
        "unsigned hexadecimal int", 
        "long int", 
        "char", 
        "float", 
        "double", 
        "long double", 
        "scientific notation float", 
        "auto-%f or %e", 
        "void *"                
    };

    int size[] = {
        sizeof(short int), 
        sizeof(int), 
        sizeof(unsigned int), 
        sizeof(unsigned int), 
        sizeof(unsigned int), 
        sizeof(long int), 
        sizeof(char), 
        sizeof(float), 
        sizeof(double), 
        sizeof(long double), 
        sizeof(double), 
        sizeof(double),
        sizeof(void), 
    };

    char *data_format[] = {
        "%hd", 
        "%d", 
        "%u", 
        "%o", 
        "%x", 
        "%ld", 
        "%c", 
        "%f", 
        "%lf", 
        "%Lf", 
        "%e", 
        "%g", 
        ""                
    };

    int num_strings = sizeof(data_types) / sizeof(data_types[0]); //字串組 組數

    size_t max_length = 0; //初始化最大長度
    for (int i = 0; i < num_strings; i++) {
        size_t length = strlen(data_types[i]);
        if (length > max_length) {
        max_length = length; // 更新最大長度
        }
    }

    for (int s = 0; s < floor(max_length/2); s++) {
            printf(" ");
        };
    printf("(type)");
    for (int s = 0; s < ceil(max_length/2)-5; s++) {
            printf(" ");
        };
    printf("(format)(byte size)\n");

    for (int j = 0; j < num_strings; j++) {
        size_t type_length = strlen(data_types[j]);
        size_t format_length = strlen(data_format[j]);

        for (int s = 0; s < max_length - type_length; s++) {
            printf(" ");
        }
        printf("%s  %s", data_types[j], data_format[j]);
        
        for (int f = 0; f < 6 - format_length; f++) {
            printf(" ");
        }
        printf("%zu bytes\n", size[j]);        
    }
    return 0;
}