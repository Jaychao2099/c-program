# include<stdio.h>
# include<string.h>
# include<stdlib.h>

# define MAX_LENGTH 50

void strcpyy(char* x, char* y){
    /*
    int i = 0;
    while ((y[i] = x[i]) != '\0')
    i++;
    */
    y = x;
}

void strswitch(char* x, char* y){
    int i = 0;
    size_t max_length = strlen(x) > strlen(y) ? strlen(x) : strlen(y);
    char* temp = malloc((max_length + 1) * sizeof(char));
    for (size_t i = 0; i < max_length; i++){
        temp[i] = x[i];
        x[i] = y[i];
        y[i] = temp[i];
    }
    free(temp);
}

int main(){                     //ENTER AB, A COPY TO C, BC CHANGE
    char A[MAX_LENGTH], B[MAX_LENGTH], C[MAX_LENGTH];

    printf("String A: ");
    scanf("%s", A);
    printf("String B: ");
    scanf("%s", B);
    printf("String C: ");
    scanf("%s", C);

    if (strlen(A) > MAX_LENGTH || strlen(B) > MAX_LENGTH || strlen(C) > MAX_LENGTH){
        printf("TOO MUCH!! Enter within %d words\n", MAX_LENGTH);
        return 1;
    }

    printf("---------\n");
    
    printf("A = %s\n", A);
    printf("B = %s\n", B);
    printf("C = %s\n", C);

    printf("---------\n");

    strcpyy(A, C);
    strswitch(B, C);

    printf("A = %s\n", A);
    printf("B = %s\n", B);
    printf("C = %s\n", C);
    
    return 0;
}