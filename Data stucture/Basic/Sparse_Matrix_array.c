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
    int current = 0;
    printf("%s =\n", x.name);
    for (int i = 0; i < x.rows; i++){
        printf("[");
        for (int j = 0; j < x.cols; j++){
            if (current < x.terms && i == x.smArray[current].row && j == x.smArray[current].col){
                printf("%4d", x.smArray[current].value);
                current++;
            } else printf("%4d", 0);
            if (j < x.cols - 1) printf(", ");
        }
        printf(" ]\n");
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
        fprintf(stderr,"ERROR: Terms of %s must be 0 ~ %d\n", name, MIN(MaxTerms, x.rows * x.cols));
        exit(1);
    }
    x.smArray = malloc(x.terms * sizeof(matrix_term));
    if (x.smArray == NULL){
        fprintf(stderr,"ERROR: unable to allocate required memory in \"input_sm\"\n");
        exit(1);
    }
    for (int i = 0; i < x.terms; i++){
        if (i > 1 && 
        ((x.smArray[i-1].row == x.smArray[i-2].row && x.smArray[i-1].col <= x.smArray[i-2].col) ||
        (x.smArray[i-1].row < x.smArray[i-2].row))){
            fprintf(stderr,"ERROR: please enter terms by order\n");
            i--;
        }
        else if (i > 0 && 
        (x.smArray[i-1].row >= x.rows || x.smArray[i-1].col >= x.cols || x.smArray[i-1].row < 0 || x.smArray[i-1].col < 0)){
            fprintf(stderr,"ERROR: row must be 0 ~ %d, column must be 0 ~ %d\n", x.rows - 1, x.cols - 1);
            i--;
        }
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
    sparse_matrix c;
    if (a.rows != b.rows || a.cols != b.cols){
        fprintf(stderr,"ERROR: size of %s(%d x %d) and %s(%d x %d) is not the same (in Addition)\n", a.name, a.rows, a.cols, b.name, b.rows, b.cols);
        c.rows = c.cols = c.terms = 0;
        c.name = name;
        return c;
    }
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
    while (a_now < a.terms && b_now < b.terms){
        if (a.smArray[a_now].row < b.smArray[b_now].row || 
            (a.smArray[a_now].row == b.smArray[b_now].row && 
             a.smArray[a_now].col < b.smArray[b_now].col)){
            if (a.smArray[a_now].value) c.smArray[c_now++] = a.smArray[a_now]; // 檢查value是否為0
            a_now++;
        } else if (a.smArray[a_now].row > b.smArray[b_now].row || 
                   (a.smArray[a_now].row == b.smArray[b_now].row && 
                    a.smArray[a_now].col > b.smArray[b_now].col)){
            if (b.smArray[b_now].value) c.smArray[c_now++] = b.smArray[b_now]; // 檢查value是否為0
            b_now++;
        } else {
            if (a.smArray[a_now].value + b.smArray[b_now].value){   // 檢查value是否為0
                c.smArray[c_now].row = a.smArray[a_now].row;
                c.smArray[c_now].col = a.smArray[a_now].col;
                c.smArray[c_now++].value = a.smArray[a_now].value + b.smArray[b_now].value;
            }
            a_now++; b_now++;
        }
    }
    
    // 處理剩餘元素
    while (a_now < a.terms){
        if (a.smArray[a_now].value) c.smArray[c_now++] = a.smArray[a_now];
        a_now++;
    }
    while (b_now < b.terms){
        if (b.smArray[b_now].value) c.smArray[c_now++] = b.smArray[b_now];
        b_now++;
    }
    
    c.terms = c_now;
    c.smArray = realloc(c.smArray, c_now * sizeof(matrix_term));
    return c;
}

sparse_matrix sm_Mult(sparse_matrix a, sparse_matrix b, char *name){
    sparse_matrix m;
    if (a.cols != b.rows){
        fprintf(stderr,"ERROR: Columns of %s must = Rows of %s (in Multiplication)\n", a.name, b.name);
        m.rows = m.cols = m.terms = 0;
        m.name = name;
        return m;
    }
    m.rows = a.rows;
    m.cols = b.cols;
    m.name = name;
    m.smArray = calloc((a.terms * b.terms), sizeof(matrix_term));

    int *row_size = calloc(a.rows, sizeof(int));    // 取得每 row 的 row size
    int *row_start = malloc(a.rows * sizeof(int));  // 取得每 row 在index 的起始位置
    if (m.smArray == NULL || row_size == NULL || row_start == NULL){
        fprintf(stderr,"ERROR: unable to allocate required memory in \"sm_Add\"\n");
        exit(1);
    }
    for (int i = 0; i < a.terms; i++) row_size[a.smArray[i].row]++;
    row_start[0] = 0;
    for (int i = 1; i < a.rows; i++) row_start[i] = row_start[i-1] + row_size[i-1];

    int m_now = 0;
    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < b.cols; j++){
            int sum = 0;
            for (int ka = row_start[i]; ka < row_start[i] + row_size[i]; ka++){
                for (int kb = 0; kb < b.terms; kb++){
                    if (a.smArray[ka].col == b.smArray[kb].row && b.smArray[kb].col == j){
                        sum += a.smArray[ka].value * b.smArray[kb].value;
                    }
                }
            }
            if (sum != 0){
                m.smArray[m_now].row = i;
                m.smArray[m_now].col = j;
                m.smArray[m_now].value = sum;
                m_now++;
            }
        }
    }
    
    m.terms = m_now;
    m.smArray = realloc(m.smArray, m_now * sizeof(matrix_term));
    free(row_size);
    free(row_start);
    return m;
}

int main(){
    int input_mode, print_mode;
    
    printf("Matrix transpose A^T\n");
    printf("Matrix transpose B^T\n");
    printf("Matrix Addition A + B = C\n");
    printf("Matrix Multiplication AB = D\n");
    printf("Input mode (1) user mode, (2) test mode:\n(1/2): ");
    scanf("%d", &input_mode);

    sparse_matrix smA;
    sparse_matrix smB;

    switch (input_mode){
        case 1:
            smA = input_sm("A");
            smB = input_sm("B");
            break;
        case 2:
            matrix_term smA_array[] = {
                {0, 0, 15}, {0, 3, 22}, {0, 5, -15},
                {1, 1, 11}, {1, 2, 3},
                {2, 3, -6},
                {4, 0, 91},
                {5, 2, 28}
            };
            matrix_term smB_array[] = {
                {1, 0, 15}, {1, 2, -3},
                {2, 1, 11},
                {3, 1, 3}, {3, 5, 28},
                {4, 0, 22}, {4, 2, -6},
                {5, 0, -15}, {5, 1, 61}, {5, 5, 17}
            };
            smA = (sparse_matrix){6, 6, sizeof(smA_array)/sizeof(matrix_term), smA_array, "A"};
            smB = (sparse_matrix){6, 6, sizeof(smB_array)/sizeof(matrix_term), smB_array, "B"};
            break;
        default:
            fprintf(stderr, "ERROR: unable to identify input_mode\n");
            return 1;
    }

    sparse_matrix smAT = transpose(smA, "A^T");
    sparse_matrix smBT = transpose(smB, "B^T");
    sparse_matrix smC  = sm_Add(smA, smB, "C");
    sparse_matrix smD  = sm_Mult(smA, smB, "D");
    
    printf("Print mode (1) sparse mode, (2) normal mode:\n(1/2): ");
    scanf("%d", &print_mode);
    switch (print_mode){
        case 1:
            printf("\n");
            print_sm(smA);     //印出 smA
            printf("\n");
            print_sm(smB);     //印出 smB
            printf("\n");
            print_sm(smAT);     //印出 smAT
            printf("\n");
            print_sm(smBT);     //印出 smBT
            printf("\n");
            print_sm(smC);      //印出 smC
            printf("\n");
            print_sm(smD);      //印出 smD
            break;
        case 2:
            printf("\n");
            print_matrix(smA);     //印出 smA
            printf("\n");
            print_matrix(smB);     //印出 smB
            printf("\n");
            print_matrix(smAT);     //印出 smAT
            printf("\n");
            print_matrix(smBT);     //印出 smBT
            printf("\n");
            print_matrix(smC);      //印出 smC
            printf("\n");
            print_matrix(smD);      //印出 smD
            break;
        default:
            fprintf(stderr, "ERROR: unable to identify print_mode\n");
            //return 1;
    }

    if (input_mode == 1) {
        free(smA.smArray);
        free(smB.smArray);
    }
    free(smAT.smArray);
    free(smBT.smArray);
    free(smC.smArray);
    free(smD.smArray);
    return 0;
}