# include <stdio.h>
# include <stdlib.h>
# include <math.h>

//# define MAX_int_PRECISION 8
//# define MAX_frac_PRECISION 16
//# define MAX_CHAR MAX_int_PRECISION + MAX_frac_PRECISION + 2

# define MAX_CHAR 30 + 2

//# define num2char(a) a + 48
# define char2num(a) a - 48

long double switch_base(int old, int new, char *input){
    long double result_d = 0;

    int dot = 0;
    while (input[dot] != 46) dot++;     //小數點位置
    
    switch (old){
        case 10:
            int integer = 0;
            for (int i = 0; i < dot; i++){              // 整數部分 變 十進位 整數
                integer += (int)char2num(input[i]) * pow(old, dot - i - 1);
            }
            for (int i = 0; integer > 0; i++){          // 整數部分
                result_d += (integer % new) * pow(10, i);
                integer /= new;
            }

            long double frac = 0;
            for (int i = dot + 1; i < MAX_CHAR; i++){   // 小數部分 變 十進位 小數
                frac += ((double)((int)char2num(input[i])) / pow(old, i - dot));
                //printf("frac = %Lf\n", frac);
            }

            for (int i = dot + 1; i < MAX_CHAR && frac > 0; i++){  // 小數部分
                frac *= new;
                result_d += (((double)((int)(frac+1e-5))) / pow(10, i - dot));
                frac = frac - ((frac > (1-1e-5)) ? 1. : 0.);
            }
            break;
        case 2:
            printf("Not yet support, ");
            return NAN;    
        default:
            printf("invalid base, ");
            return NAN;
        }

    return result_d;
}

int main(){
    int base_old, base_new;
    char input_char[MAX_CHAR];
    long double output_num;

    printf("Original base: ");
    scanf("%d", &base_old);
    if (base_old != 2 && base_old != 10){
        printf("Base must be 2 or 10\n");
        return 1;
    }
    base_new = base_old == 10 ? 2 : 10;
    printf("base %d --> base %d\n", base_old, base_new);
    
    printf("(within %d word, includind \".\")\nNumber: ", MAX_CHAR);
    getchar();  // 清除之前輸入的換行符
    for (int i = 0; i < MAX_CHAR; i++){
        scanf("%c", &input_char[i]);
    }

    output_num = switch_base(base_old, base_new, input_char);

    if (output_num == NAN) {
        fprintf(stderr, "Error in calculation\n");
        return 1;
    }
    
    printf("Answer: %.28Lf", output_num);

    return 0;
}