# include <stdio.h>

int sum(int a, int b, int c){
    int result = (a ^ b) ^ c;
    return result;
}

int Cout(int a, int b, int c){
    //int result = ((a ^ b) & c) | (a & b);
    int result = (a & b) | (a & c) | (b & c);
    return result;
}

int main(){
    printf("  input  | output\n");
    printf(" A B Cin | Cout S\n");
    printf("------------------\n");
    int A, B, C, S, Co;
    for(int i = 0; i < 8; i++){
        C = i / 4;
        B = (i % 4) / 2;
        A = (i % 2) / 1;
        S = sum(A, B, C);
        Co = Cout(A, B, C);
        printf(" %d %d  %d  |  %d   %d\n", A, B, C, Co, S);
    }
    return 0;
}