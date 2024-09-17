# include <stdio.h>

int main(){
    char input;

    for (int i = 32; i < 128; i++){
        input = i;
        printf("%d: %c\n", i,input);
    }

    return 0;
}