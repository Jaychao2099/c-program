# include <stdio.h>
# include <stdlib.h>

# define MaxTerms 100   //大陣列的最多容量

// 矩陣的項 {row, column, value}
typedef struct matrix_term{
    int row;    //列
    int col;    //行
    int value;  //值
}matrix_term;

// 稀疏矩陣 {total rows, total columns, total terms, name of matrix}
typedef struct sparse_matrix{
    int rows;   //總rows數
    int cols;   //總columns數
    int terms;  //總terms數
    matrix_term *smArray;    //稀疏矩陣 陣列
    char* name;  //名稱
}sparse_matrix;

void print_sm(sparse_matrix x){
}

sparse_matrix input_sm(int rows, int columns, int terms, char *name){
}

sparse_matrix transpose(sparse_matrix x, char *name){
}

sparse_matrix sm_Mult(sparse_matrix a, sparse_matrix b, char *name){
}

int main(){
    int rows_A, columns_A, rows_B, columns_B;
    int terms_A, terms_B;       //項數
    
    printf("Matrix transpose A^T <= A\n");
    printf("Matrix transpose B^T <= B\n");
    printf("Matrix Multiplication C = AB\n");

    printf("Rows in A: ");
    scanf("%d", &rows_A);
    printf("Columns in A: ");
    scanf("%d", &columns_A);
    printf("Rows in B: %d\n", columns_A);
    rows_B = columns_A;
    printf("Columns in B: ");
    scanf("%d", &columns_B);
    printf("How many terms in A? ");
    scanf("%d", &terms_A);
    printf("How many terms in B? ");
    scanf("%d", &terms_B);
    if (terms_A >= MaxTerms || terms_B >= MaxTerms || terms_A < 0 || terms_B < 0){
        printf("Each terms must between 0 ~ %d", MaxTerms);
        return 1;
    }

    sparse_matrix smA = input_sm(rows_A, columns_A, terms_A, "A");     //大陣列取得 poly_A 的資料
    sparse_matrix smB = input_sm(rows_B, columns_B, terms_B, "B");     //大陣列取得 poly_B 的資料

    sparse_matrix smAT = transpose(smA, "A^T");
    sparse_matrix smBT = transpose(smB, "B^T"); 
    sparse_matrix smC  = sm_Mult(smA, smB, "C");
    

    printf("\n");
    print_sm(smAT);     //印出 smAT
    printf("\n");
    print_sm(smBT);     //印出 smBT
    printf("\n");
    print_sm(smC);      //印出 smC

    //free(total_poly.termArray);

    return 0;
}