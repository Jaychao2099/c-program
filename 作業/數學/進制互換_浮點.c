# include <stdio.h>
# include <stdlib.h>
# include <math.h>

long double switch_base(int old, int new, long double input){
    long double result = 0.;
    
    int integer = (int)input;
    long double frac = input - (long double)(int)input;

    for (int i = 0; integer > 0; i++){          // 整數部分
        result += (integer % new) * pow(10, i);
        integer /= new;
    }

    for (int i = 1; i < 16 && frac > 0; i++){  // 小數部分
        frac *= new;
        result += ((int)(frac)) * pow(10, -i);
        frac -= (frac >= 1) ? 1 : 0;
    }

    return result;
}

int main(){
    int base_old, base_new;
    long double input_num, output_num;

    printf("Original base: ");
    scanf("%d", &base_old);
    if (base_old != 2 && base_old != 10){
        printf("Base must be 2 or 10\n");
        return 1;
    }
    base_new = base_old == 10 ? 2 : 10;
    printf("base %d --> base %d\n", base_old, base_new);
    
    printf("Number: ");
    scanf("%Lf", &input_num);

    output_num = switch_base(base_old, base_new, input_num);
    
    printf("Answer: %.16Lf", output_num);

    return 0;
}