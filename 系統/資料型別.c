#include <stdio.h>
#include <string.h>

int main(){
    char *data_types[] = {
        "short int", 
        "int", 
        "unsigned int", 
        "unsigned octal int", 
        "unsigned hexadecimal int", 
        "long int", 
        "long long",
        "char", 
        "wchar_t", 
        "float", 
        "double", 
        "long double", 
        "scientific notation float", 
        "auto %f or %e", 
        "_Bool",
        "void"           
    };

    int size[] = {
        sizeof(short int), 
        sizeof(int), 
        sizeof(unsigned int), 
        sizeof(unsigned int), 
        sizeof(unsigned int), 
        sizeof(long int), 
        sizeof(long long), 
        sizeof(char), 
        sizeof(wchar_t), 
        sizeof(float), 
        sizeof(double), 
        sizeof(long double), 
        sizeof(double), 
        sizeof(double),
        sizeof(_Bool),
        sizeof(void)
    };

    char *data_format[] = {
        "%hd", 
        "%d", 
        "%u", 
        "%o", 
        "%x", 
        "%ld", 
        "%lld", 
        "%c", 
        "%lc", 
        "%f", 
        "%lf", 
        "%Lf", 
        "%e", 
        "%g", 
        "%d",
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

    for (int s = 0; s < max_length/2; s++) {
            printf(" ");
        }
    printf("(type)");
    for (int s = 0; s < max_length/2+1 - 5; s++) {
            printf(" ");
        }
    printf("(format)(byte size)\n");

    for (int j = 0; j < num_strings; j++) {
        size_t type_length = strlen(data_types[j]);
        size_t format_length = strlen(data_format[j]);
        size_t size_length = size[j] / 10 + 1;

        for (int s = 0; s < max_length - type_length; s++) {
            printf(" ");
        }
        printf("%s  %s", data_types[j], data_format[j]);
        
        for (int f = 0; f < 6 - format_length; f++) {
            printf(" ");
        }

        for (int b = 0; b < 2 - size_length; b++) {
            printf(" ");
        }
        printf("%zu bytes\n", size[j]);       
    }
    return 0;
}