# include<stdio.h>
# include<string.h>
# include<stdlib.h>

void strcpy_B_to_A(char* x, char* y){
    int i = 0;
    while ((x[i] = y[i]) != '\0')
    i++;
}

void strswitch(char* x, char* y){
    int i = 0;
    size_t length_x = strlen(x);
    size_t length_y = strlen(y);
    size_t max_length = length_x > length_y ? length_x : length_y;
    char* temp = malloc(max_length * sizeof(char));
    for (size_t i = 0; i < max_length; i++){
        temp[i] = x[i];
        x[i] = y[i];
        y[i] = temp[i];
    }
    free(temp);
}

int main(){                     //ENTER AB, A COPY TO C, BC CHANGE
    char A[20] = "";
    char *B = "123DWED1E2";
    char* C;

    printf("A = %s\n", A);
    printf("B = %s\n", B);
    printf("---------\n");

    strcpy_B_to_A(A, B);

    printf("A = %s\n", A);
    printf("B = %s\n", B);
    return 0;
}