# include<stdio.h>
# include<string.h>
# include<stdlib.h>

void strcpyy(char* x, char* y){
    int i = 0;
    while ((y[i] = x[i]) != '\0')
    i++;
}

void strswitch(char* x, char* y){
    int i = 0;
    size_t max_length = strlen(x) > strlen(y) ? strlen(x) : strlen(y);
    char* temp = malloc(max_length * sizeof(char));
    for (size_t i = 0; i < max_length; i++){
        temp[i] = x[i];
        x[i] = y[i];
        y[i] = temp[i];
    }
    free(temp);
}

int main(){                     //ENTER AB, A COPY TO C, BC CHANGE
    char A[20], B[20], C[20];

    printf("String A: ");
    scanf("%20s", A);
    printf("String B: ");
    scanf("%20s", B);
    printf("String C: ");
    scanf("%20s", C);

    printf("---------\n");

    strcpyy(A, C);
    strswitch(B, C);

    printf("A = %s\n", A);
    printf("B = %s\n", B);
    printf("C = %s\n", C);
    return 0;
}