# include <stdio.h>
# include <stdlib.h>

# define MaxTerms 100   //大陣列的最多容量
# define MIN(a, b) ((a < b) ? a : b)

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
    char *name;  //名稱
}sparse_matrix;

void print_matrix(sparse_matrix x){
    int current;
    printf("%s =\n", x.name);
    for (int i = 0; i < x.rows; i++){
        printf("[");
        for (int j = 0; i < x.cols; i++){
            if (i == x.smArray[current].row && j == x.smArray->col){
                printf("%d, ", x.smArray[current].value);
                current++;
            } else printf("0, ");
        }
        printf("]\n");
    }
}

void print_sm(sparse_matrix x){
    for (int i = 0; i < x.terms; i++){
        printf("%s[%d] = ", x.name, i);
        printf("%d\t%d\t%d\n", x.smArray[i].row, x.smArray[i].col, x.smArray[i].value);
    }
}

sparse_matrix input_sm(char *name){
    sparse_matrix x;
    x.name = name;
    printf("Rows\tin %s: ", name);
    scanf("%d", &x.rows);
    printf("Columns\tin %s: ", name);
    scanf("%d", &x.cols);
    if (x.rows < 0 || x.cols < 0){
        fprintf(stderr,"ERROR: Rows and Columns must > 0\n");
        exit(1);
    }
    printf("Terms\tin %s: ", name);
    scanf("%d", &x.terms);
    if (x.terms > MaxTerms || x.terms > x.rows * x.cols || x.terms < 0){
        fprintf(stderr,"ERROR: Terms of %s must between 0 ~ %d\n", name, MIN(MaxTerms, x.rows * x.cols));
        exit(1);
    }
    x.smArray = malloc(x.terms * sizeof(matrix_term));
    if (x.smArray == NULL){
        fprintf(stderr,"ERROR: unable to allocate required memory in \"input_sm\"\n");
        exit(1);
    }
    for (int i = 0; i < x.terms; i++){
        printf("%d. ", i + 1);
        scanf("%d%d%d", &x.smArray[i].row, &x.smArray[i].col, &x.smArray[i].value);
        printf("%d. [%d, %d] = %d\n", i + 1, x.smArray[i].row, x.smArray[i].col, x.smArray[i].value);
    }
    return x;
}

sparse_matrix transpose(sparse_matrix x, char *name){
    sparse_matrix t;
    t.rows = x.cols;
    t.cols = x.rows;
    t.terms = x.terms;
    t.name = name;
    if (x.terms > 0){
        int *row_size = calloc(x.cols, sizeof(int));
        int *row_start = malloc(x.cols * sizeof(int));
        t.smArray = malloc(t.terms * sizeof(matrix_term));
        if (t.smArray == NULL || row_size == NULL || row_start == NULL){
            fprintf(stderr,"ERROR: unable to allocate required memory in \"transpose\"\n");
            exit(1);
        }
        for (int i = 0; i < x.terms; i++) row_size[x.smArray[i].col]++; // 取得每 row 的 row size
        row_start[0] = 0;
        for (int i = 1; i < x.cols; i++) row_start[i] = row_start[i-1] + row_size[i-1]; //取得每 row 在index 的起始位置
        for (int i = 0; i < t.terms; i++){
            int j = row_start[x.smArray[i].col];    // 依據原col號 在其對應的新起始位置加入元素
            t.smArray[j].row = x.smArray[i].col;
            t.smArray[j].col = x.smArray[i].row;
            t.smArray[j].value = x.smArray[i].value;
            row_start[x.smArray[i].col]++;          // 該col號已用掉一個元素 start前進一格
        }
        free(row_size);
        free(row_start);
    }
    return t;
}

sparse_matrix sm_Add(sparse_matrix a, sparse_matrix b, char *name){
    if (a.rows != b.rows || a.cols != b.cols){
        fprintf(stderr,"ERROR: size of %s(%d x %d) and %s(%d x %d) is not the same (in Addition)\n", a.name, a.rows, a.cols, b.name, b.rows, b.cols);
        exit(1);
    }
    sparse_matrix c;
    c.rows = a.rows;
    c.cols = a.cols;
    c.name = name;
    c.smArray = malloc((a.terms + b.terms) * sizeof(matrix_term));
    if (c.smArray == NULL){
        fprintf(stderr,"ERROR: unable to allocate required memory in \"sm_Add\"\n");
        exit(1);
    }
    int a_now = 0;
    int b_now = 0;
    int c_now = 0;
    while (a_now <= a.terms && b_now <= b.terms){
        if (a.smArray[a_now].row < b.smArray[b_now].row){
            c.smArray[c_now].row = a.smArray[a_now].row;
            c.smArray[c_now].col = a.smArray[a_now].col;
            c.smArray[c_now].value = a.smArray[a_now].value;
            a_now++;
            c_now++;
        }
        if (a.smArray[a_now].row > b.smArray[b_now].row){
            c.smArray[c_now].row = b.smArray[b_now].row;
            c.smArray[c_now].col = b.smArray[b_now].col;
            c.smArray[c_now].value = b.smArray[b_now].value;
            b_now++;
            c_now++;
        }
        if (a.smArray[a_now].row = b.smArray[b_now].row){
            if (a.smArray[a_now].col < b.smArray[b_now].col){
                c.smArray[c_now].row = a.smArray[a_now].row;
                c.smArray[c_now].col = a.smArray[a_now].col;
                c.smArray[c_now].value = a.smArray[a_now].value;
                a_now++;
                c_now++;
            }
            if (a.smArray[a_now].col > b.smArray[b_now].col){
                c.smArray[c_now].row = b.smArray[b_now].row;
                c.smArray[c_now].col = b.smArray[b_now].col;
                c.smArray[c_now].value = b.smArray[b_now].value;
                b_now++;
                c_now++;
            }
            if (a.smArray[a_now].col = b.smArray[b_now].col){
                c.smArray[c_now].row = b.smArray[b_now].row;
                c.smArray[c_now].col = b.smArray[b_now].col;
                c.smArray[c_now].value = a.smArray[a_now].value + b.smArray[b_now].value;
                a_now++;
                b_now++;
                c_now++;
            }
        }
    }
    c.terms = c_now;
    c.smArray = realloc(c.smArray, c_now * sizeof(matrix_term));
    return c;
}

sparse_matrix sm_Mult(sparse_matrix a, sparse_matrix b, char *name){
    if (a.cols != b.rows){
        fprintf(stderr,"ERROR: Columns of %s must = Rows of %s (in Multiplication)\n", a.name, b.name);
        exit(1);
    }
    sparse_matrix m;
    m.rows = a.rows;
    m.cols = b.cols;
    m.name = name;
    m.smArray = calloc((a.terms * b.terms), sizeof(matrix_term));
    if (m.smArray == NULL){
        fprintf(stderr,"ERROR: unable to allocate required memory in \"sm_Add\"\n");
        exit(1);
    }
    int *row_size = calloc(a.rows, sizeof(int));
    int *row_end = malloc(a.rows * sizeof(int));
    for (int i = 0; i < a.terms; i++) row_size[a.smArray[i].row]++; // 取得每 row 的 row size
    for (int i = 0; i < a.rows; i++) row_end[i] = row_end[i-1] + row_size[i]; //取得每 row 在index 的終點位置

    int m_now = 0;
    int a_now = 0;
    for (int i = 0; i < a.rows; i++){
        for (int j = a_now; j < row_end[i]; j++){
            for (int k = 0; k < b.terms; k++){
                if (a.smArray[i].row == b.smArray[k].col){
                    m.smArray[m_now].row = a.smArray[i].row;
                    m.smArray[m_now].col = b.smArray[k].col;
                    m.smArray[m_now].value += a.smArray[i].value * b.smArray[k].value;
                }
            }
            m_now++;
            a_now++;
        }
    }
    free(row_size);
    free(row_end);
    return m;
}

int main(){
    int rows_B, cols_B, terms_B;
    
    printf("Matrix transpose A^T\n");
    printf("Matrix transpose B^T\n");
    printf("Matrix Addition A + B = C\n");
    printf("Matrix Multiplication AB = D\n");

    sparse_matrix smA = input_sm("A");
    sparse_matrix smB = input_sm("B");

    sparse_matrix smAT = transpose(smA, "A^T");
    sparse_matrix smBT = transpose(smB, "B^T");
    sparse_matrix smC  = sm_Add(smA, smB, "C");
    sparse_matrix smD  = sm_Mult(smA, smB, "D");
    
    printf("\n");
    print_sm(smAT);     //印出 smAT
    printf("\n");
    print_sm(smBT);     //印出 smBT
    printf("\n");
    print_sm(smC);      //印出 smC
    printf("\n");
    print_sm(smD);      //印出 smD

    free(smA.smArray);
    free(smB.smArray);
    free(smAT.smArray);
    free(smBT.smArray);
    free(smC.smArray);
    free(smD.smArray);

    return 0;
}