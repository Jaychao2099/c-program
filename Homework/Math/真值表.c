# include <stdio.h>

int logic_1(int a, int b, int c){
    int result = (a & b) | ((a & c) | (b & c));
    return result;
}

int logic_2(int a, int b, int c){
    int result = (a & b) | ((a ^ b) & c);
    return result;
}

int main(){
    printf(" input | output\n");
    printf(" A B C | logic_1 logic_2\n");
    printf("-------------------------\n");
    int A, B, C, l1, l2;
    for(int i = 0; i < 8; i++){
        C = i / 4;
        B = (i % 4) / 2;
        A = (i % 2) / 1;

        l1 = logic_1(A, B, C);
        l2 = logic_2(A, B, C);
        printf(" %d %d %d |    %d       %d\n", A, B, C, l1, l2);
    }
    return 0;
}