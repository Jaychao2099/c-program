# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define MAX_CHAR_10_2 18
# define MAX_CHAR_2_10 32

//# define num2char(a) a + 48
# define char2num(a) a - 48

long double switch_base(int old, int new, char *input){
    int integer = 0;
    long double frac = 0, result_d = 0;

    int dot = 0;
    while (input[dot] != 46) dot++;     //小數點位置

    int max = (old == 10) ? MAX_CHAR_10_2 : MAX_CHAR_2_10;
    
    int temp_old_int = 1;
    long long int temp_old_frac = old;
    for (int i = 0; i < dot; i++){              // 整數部分 變 old 進位 整數
        integer += (int)(char2num(input[dot-i-1])) * temp_old_int;
        temp_old_int *= old;
    }
    for (int i = dot + 1; i < max; i++){   // 小數部分 變 old 進位 小數
        frac += (long double)((int)char2num(input[i])) / temp_old_frac;
        printf("i = %d, %.21Lf += %.21Lf / %lld\n", i, frac, (long double)((int)char2num(input[i])), temp_old_frac);
        temp_old_frac *= old;
    }
    switch (old){
        case 10:
            int temp10 = 1;
            for (int i = 0; integer > 0; i++){          // 整數部分
                result_d += (integer % new) * temp10;
                integer /= new;
                temp10 *= 10;
            }
            long long int temp10_long = 10;
            for (int i = dot + 1; i < max && frac > 0; i++){  // 小數部分
                frac *= new;
                result_d += (floor(frac+1e-5) / temp10_long);
                frac = frac - ((frac > (1-1e-5)) ? 1. : 0.);
                temp10_long *= 10;
            }
            return result_d;
        case 2:
            return (long double)(integer) + frac;
        default:
            printf("invalid base, ");
            return NAN;
        }
}

int main(){
    int base_old, base_new;
    long double output_num;

    printf("Original base: ");
    scanf("%d", &base_old);
    if (base_old != 2 && base_old != 10){
        printf("Base must be 2 or 10\n");
        return 1;
    }
    base_new = base_old == 10 ? 2 : 10;
    printf("base %d --> base %d\n", base_old, base_new);

    int max = (base_old == 10) ? MAX_CHAR_10_2 : MAX_CHAR_2_10;

    char input_char[max];
    
    printf("(within %d word, includind \".\")\nNumber: ", max);
    getchar();  // 清除之前輸入的換行符
    for (int i = 0; i < max; i++){
        scanf("%c", &input_char[i]);
    }

    output_num = switch_base(base_old, base_new, input_char);

    if (output_num == NAN) {
        fprintf(stderr, "Error in calculation\n");
        return 1;
    }
    
    
    switch (base_new){
        case 2:
            printf("Answer: %.16Lf", output_num);
            break;
        case 10:
            printf("Answer: %.9Lf", output_num);
            break;
        default:
            printf("error: Base must be 2 or 10\n");
            break;
    }

    return 0;
}