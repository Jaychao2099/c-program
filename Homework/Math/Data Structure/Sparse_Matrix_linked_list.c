# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

# define MAXHEAD 1000

typedef struct node{
    int row, col, value;            // entry node 的所在 row, col, 值
    struct node *down, *right;      // 把同一 col, row 連起來
    struct node *next;  // 連下一個 head node
    bool head;          // 是否為 head node
}node;

typedef struct{
    node *head_first;
    node *head_last;
    char *name;
}Matrix;

void print_sm(Matrix *m){
    node *current = m->head_first->next->right;
    int i = 0;
    while (current != m->head_first){
        if (current->head){
            current = current->next->right;
        }
        else {
            printf("%s[%d] = ", m->name, i);
            printf("[%d, %d] = %3d\n", current->row, current->col, current->value);
            current = current->right;
            i++;
        }
    }
    if (i != m->head_first->value){
        printf("ERROR: entry count fault. value = %d, i = %d\n", m->head_first->value, i);
        printf("total = (%d, %d)\n", m->head_first->row, m->head_first->col);
    }
}

void print_matrix(Matrix *m){
    printf("%s =\n", m->name);
    node *current_row = m->head_first->next;
    for (int i = 0; i < m->head_first->row; i++){   // H0 起始
        printf("[");
        current_row->col = m->head_first->col;      // 給予 head node col 總數，以便計算 zero_size
        int zero_size = -1;
        node *current_col = current_row->right;     // 歷遍 col
        int j = 0;
        while (j < m->head_first->col){             // 印出一 row
            zero_size = current_col->col - zero_size - 1;           // 與上一個元素的 col 差距
            for (int k = 0; k < zero_size; k++){
                printf("   0");
                // if (j < m->head_first->col - 1)
                //     printf(",");
                j++;
            }
            if (current_col != current_row){
                printf("%4d", current_col->value);
                // if (j < m->head_first->col - 1)
                //     printf(",");
                j++;
            }
            zero_size = current_col->col;
            current_col = current_col->right;
        }
        printf(" ]\n");
        current_row->col = 0;           // head node 的 col 數歸零
        current_row = current_row->next;
    }
}

// create node
node *create_node(int row, int col, int value, bool head, Matrix *freelist){
    node *newnode;
    if (freelist->head_first){                            // 可用 freelist 的空間
        newnode = freelist->head_first;                   // 用 freelist 的第一個空間
        freelist->head_first = freelist->head_first->next;
    }
    else {
        newnode = malloc(sizeof(node));    // 請求一個新空間
        if (newnode == NULL){
            printf("ERROR: unable to allocate required memory in create_node\n");
            exit(1);
        }
    }
    *newnode = (node){row, col, value, newnode, newnode, NULL, head};   // down, right 指向自己
    return newnode;
}

void append_head_node(Matrix *m, node *newnode, Matrix *freelist){
    // if m is empty, create head head node
    if (m->head_first == NULL){
        m->head_first = m->head_last = create_node(0, 0, 0, true, freelist);
    }
    // append head node
    while (m->head_first->row < newnode->row + 1 || m->head_first->col < newnode->col + 1){
        node *new_head = create_node(0, 0, 0, true, freelist);
        new_head->next = m->head_first;
        m->head_last->next = new_head;
        m->head_last = new_head;
        if (m->head_first->row < newnode->row + 1) m->head_first->row++;
        if (m->head_first->col < newnode->col + 1) m->head_first->col++;
    }
}

void append_entry_node(Matrix *m, node *newnode){
    node *ptr_head = m->head_first;
    
    // 調整 right 指標
    for (int i = 0; i <= newnode->row; i++){    // 指標指到該 row
        ptr_head = ptr_head->next;
    }
    node *ptr_entry = ptr_head;
    while (ptr_entry->right != ptr_head){       // 指標指到該 row 最後一個元素
        ptr_entry = ptr_entry->right;
    }
    newnode->right = ptr_head;
    ptr_entry->right = newnode;                 // 修改最後一個元素的 ->right 指向
    
    // 調整 down 指標
    ptr_head = m->head_first;
    for (int i = 0; i <= newnode->col; i++){    // 指標指到該 col
        ptr_head = ptr_head->next;
    }
    ptr_entry = ptr_head;
    while (ptr_entry->down != ptr_head){        // 指標指到該 col 最後一個元素
        ptr_entry = ptr_entry->down;
    }
    newnode->down = ptr_head;
    ptr_entry->down = newnode;                  // 修改最後一個元素的 ->down 指向

    m->head_first->value++;     // 總 entry 增加
}

// append node
void append_node(Matrix *m, node *newnode, Matrix *freelist){
    append_head_node(m, newnode, freelist);
    append_entry_node(m, newnode);
}

// concatenating M -> newlist
void append_list(Matrix *M, Matrix *newlist){
    if (M->head_first == NULL){
        M->head_first = newlist->head_first;
        M->head_last = newlist->head_last;
    }
    else {
        M->head_last->next = newlist->head_first;
        M->head_last = newlist->head_last;
        M->head_last->next = M->head_first;
    }
    newlist->head_first = newlist->head_last = NULL;     // 讓 newlist 消失
}

// delete whole M
void remove_list(Matrix *m){
    node *current = m->head_first->next->right;
    while (current != m->head_first){
        node *temp;
        if (current->head){
            temp = current->next->right;
        }
        else temp = current->right;
        free(current);
        current = temp;
    }
    free(current);
}

void input_sm(Matrix *m, Matrix *freelist){
    node *entry;
    printf("(Enter -1 to stop)\n");
    printf("%s =\n", m->name);
    for (int i = 0; i < MAXHEAD * MAXHEAD; i++){
        int row = 0, col = 0, value;
        while (1){
            printf("%d. ", i + 1);
            scanf("%d", &row);
            if (row == -1) return;      // 輸入 -1 停止輸入
            scanf("%d%d", &col, &value);
            if (row >= MAXHEAD || row < 0 || col >= MAXHEAD || col < 0)
                printf("ERROR: row and col must be 0 ~ %d", MAXHEAD);
            else if (i == 0 || ((entry->row == row && entry->col < col) || (entry->row < row)))    // 檢查是否由上到下，由左到右輸入
                break;
            else printf("ERROR: please enter terms by order\n");
        }

        append_node(m, create_node(row, col, value, false, freelist), freelist);
        node *current = m->head_first;
        do {
            while (current->head){
                current = current->next->right;
                if (current == m->head_first) break;
            }
            while (!current->head){
                entry = current;
                current = current->right;
            }
        } while (current != m->head_first);
        printf("%d. [%d, %d] = %d\n", i + 1, entry->row, entry->col, entry->value);     // 印出檢查
    }
}

// 轉置函數，建立新矩陣
Matrix *transpose(Matrix *m, Matrix *freelist){
    if (!m || !m->head_first) return NULL;

    // 創建轉置矩陣
    Matrix *t = calloc(1, sizeof(Matrix));

    node *current = m->head_first->next->right;
    while (current != m->head_first){
        if (current->head){
            current = current->next->right;
        }
        else {
            append_node(t, create_node(current->col, current->row, current->value, false, freelist), freelist);
            current = current->right;
        }
    }
    // 更改名字
    char *str = malloc((strlen(m->name) + 5) * sizeof(char));
    if (str == NULL){
        puts("\nERROR: unable to change name\n");
        return t;
    }
    strcpy(str, "(");
    strcat(str, m->name);
    strcat(str, ")^T");
    t->name = str;

    return t;
}

// 轉置函數，原矩陣改變 pointer
void transpose_change_pointer(Matrix *m){
    node *current = m->head_first;
    do {    // 交換 row, col 數字
        int temp_int = current->row;
        current->row = current->col;
        current->col = temp_int;
            // 移動 current
        if (current->head){
            current = current->next->right;
        }
        else
            current = current->down;
            // 交換 down, right 指標
        node *temp = current->right;
        current->right = current->down;
        current->down = temp;
    } while (current != m->head_first);
    
    // 更改名字
    char *str = malloc((strlen(m->name) + 5) * sizeof(char));
    if (str == NULL){
        puts("\nERROR: unable to change name\n");
        return;
    }
    strcpy(str, "(");
    strcat(str, m->name);
    strcat(str, ")^T");
    m->name = str;
}

Matrix *sm_Add(Matrix *a, Matrix *b, Matrix *freelist){
    if (a->head_first->row != b->head_first->row || a->head_first->col != b->head_first->col){
        printf("ERROR: size of %s(%d x %d) and %s(%d x %d) is not the same (in Addition)\n", a->name, a->head_first->row, a->head_first->col, b->name, b->head_first->row, b->head_first->col);
        return NULL;
    }
    Matrix *s = calloc(1, sizeof(Matrix));
    if (s == NULL){
        printf("ERROR: unable to allocate required memory in \"sm_Add\"\n");
        exit(1);
    }

    node *a_now = a->head_first->next->right;
    node *b_now = b->head_first->next->right;
    while (a_now != a->head_first && b_now != b->head_first){
        while (a_now->head && a_now != a->head_first) a_now = a_now->next->right;
        while (b_now->head && b_now != b->head_first) b_now = b_now->next->right;
        if      (a_now == a->head_first);
        else if (b_now == b->head_first);
        else if (a_now->row < b_now->row || (a_now->row == b_now->row && a_now->col < b_now->col)){
            if (a_now->value){      // 檢查value是否為0
                append_node(s, create_node(a_now->row, a_now->col, a_now->value, false, freelist), freelist);
            }
            a_now = a_now->right;
        }
        else if (b_now->row < a_now->row || (b_now->row == a_now->row && b_now->col < a_now->col)){
            if (b_now->value){      // 檢查value是否為0
                append_node(s, create_node(b_now->row, b_now->col, b_now->value, false, freelist), freelist);
            }
            b_now = b_now->right;
        } else {
            if (a_now->value + b_now->value){   // 檢查value是否為0
                append_node(s, create_node(a_now->row, a_now->col, a_now->value + b_now->value, false, freelist), freelist);
            }
            a_now = a_now->right;
            b_now = b_now->right;
        }
    }
    
    // 處理剩餘元素
    while (a_now != a->head_first){
        while (a_now->head && a_now != a->head_first) a_now = a_now->next->right;
        if (a_now == a->head_first);
        else if (a_now->value){      // 檢查value是否為0
            append_node(s, create_node(a_now->row, a_now->col, a_now->value, false, freelist), freelist);
        }
        a_now = a_now->right;
    }
    while (b_now != b->head_first){
        while (b_now->head && b_now != b->head_first) b_now = b_now->next->right;
        if (b_now == b->head_first);
        else if (b_now->value){      // 檢查value是否為0
            append_node(s, create_node(b_now->row, b_now->col, b_now->value, false, freelist), freelist);
        }
        b_now = b_now->right;
    }

    // 更改名字
    s->name = malloc((strlen(a->name) + strlen(b->name) + 6) * sizeof(char));
    if (s->name == NULL){
        puts("\nERROR: unable to change name\n");
        return s;
    }
    strcpy(s->name, "(");
    strcat(s->name, a->name);
    strcat(s->name, " + ");
    strcat(s->name, b->name);
    strcat(s->name, ")");

    return s;
}

Matrix *sm_Multi(Matrix *a, Matrix *b, Matrix *freelist){
    Matrix *m = calloc(1, sizeof(Matrix));

    int temp_a_row = 0;     // 臨時計算 當前 a row
    for (node *i = a->head_first->next; i != a->head_first; i = i->next){
        // while (i->head) i = i->next->right;
        // if (i = a->head_first) break;
        int temp_b_col = 0;     // 臨時計算 當前 b col
        for (node *j = b->head_first->next; j != b->head_first; j = j->next){
            int sum = 0;
            for (node *ka = i->right; ka != i; ka = ka->right){
                for (node *kb = j->down; kb != j; kb = kb->down){
                    if (ka->col == kb->row){
                        sum += ka->value * kb->value;
                    }
                }
            }
            if (sum){
                append_node(m, create_node(temp_a_row, temp_b_col, sum, false, freelist), freelist);
            }
            temp_b_col++;
        }
        temp_a_row++;
    }

    // 更改名字
    m->name = malloc((strlen(a->name) + strlen(b->name) + 4) * sizeof(char));
    if (m->name == NULL){
        puts("\nERROR: unable to change name\n");
        return m;
    }
    strcpy(m->name, "(");
    strcat(m->name, a->name);
    strcat(m->name, "*");
    strcat(m->name, b->name);
    strcat(m->name, ")");

    return m;
}

int main(){
    int input_mode, print_mode;

    printf("Matrix transpose A^T\n");
    printf("Matrix transpose B^T\n");
    printf("Matrix Addition A + B\n");
    printf("Matrix Multiplication AB\n\n");
    while (1){
        printf("Input mode 1.user mode, 2.test mode (1/2): ");
        scanf("%d", &input_mode);
        if (input_mode == 1 || input_mode == 2) break;
        else printf("ERROR: invalid input mode\n");
    }

    Matrix freelist = {NULL, NULL};
    Matrix *smA = (Matrix *)calloc(1, sizeof(Matrix)); smA->name = "A";
    Matrix *smB = (Matrix *)calloc(1, sizeof(Matrix)); smB->name = "B";

    switch (input_mode){
        case 1:
            input_sm(smA, &freelist);
            input_sm(smB, &freelist);
            break;
        case 2:
            append_node(smA, create_node(0, 0,  15, 0, &freelist), &freelist);
            append_node(smA, create_node(0, 3,  22, 0, &freelist), &freelist);
            append_node(smA, create_node(0, 5, -15, 0, &freelist), &freelist);
            append_node(smA, create_node(1, 1,  11, 0, &freelist), &freelist);
            append_node(smA, create_node(1, 2,   3, 0, &freelist), &freelist);
            append_node(smA, create_node(2, 3,  -6, 0, &freelist), &freelist);
            append_node(smA, create_node(4, 0,  91, 0, &freelist), &freelist);
            append_node(smA, create_node(5, 2,  28, 0, &freelist), &freelist);
            
            append_node(smB, create_node(1, 0,  15, 0, &freelist), &freelist);
            append_node(smB, create_node(1, 2,  -3, 0, &freelist), &freelist);
            append_node(smB, create_node(2, 1,  11, 0, &freelist), &freelist);
            append_node(smB, create_node(3, 1,   3, 0, &freelist), &freelist);
            append_node(smB, create_node(3, 5,  28, 0, &freelist), &freelist);
            append_node(smB, create_node(4, 0,  22, 0, &freelist), &freelist);
            append_node(smB, create_node(4, 2,  -6, 0, &freelist), &freelist);
            append_node(smB, create_node(5, 0, -15, 0, &freelist), &freelist);
            append_node(smB, create_node(5, 1,  61, 0, &freelist), &freelist);
            append_node(smB, create_node(5, 5,  17, 0, &freelist), &freelist);
            break;
        default:
            printf("ERROR: unable to identify input_mode\n");
            return 1;
    }

    Matrix *smAT = transpose(smA, &freelist);
    Matrix *smBT = transpose(smB, &freelist);

    Matrix *smS = sm_Add(smA, smB, &freelist);
    Matrix *smM = sm_Multi(smA, smB, &freelist);

    while (1){
        printf("Print mode: 1.sparse mode, 2.normal mode, 3.pointer transpose mode (1/2/3): ");
        scanf("%d", &print_mode);
        if (print_mode == 1 || print_mode == 2 || print_mode == 3) break;
        else printf("ERROR: invalid print mode\n");
    }
    switch (print_mode){
        case 1:
            printf("\n");
            print_sm(smA);     //印出 smA
            printf("\n");
            print_sm(smB);     //印出 smB

            printf("\n");
            print_sm(smAT);     //印出 smAT
            append_list(&freelist, smAT);
            printf("\n");
            print_sm(smBT);     //印出 smBT
            append_list(&freelist, smBT);

            printf("\n");
            print_sm(smS);      //印出 smS
            append_list(&freelist, smS);
            printf("\n");
            print_sm(smM);      //印出 smM
            append_list(&freelist, smM);
            break;
        case 2:
            printf("\n");
            print_matrix(smA);     //印出 smA
            printf("\n");
            print_matrix(smB);     //印出 smB

            printf("\n");
            print_matrix(smAT);     //印出 smAT
            append_list(&freelist, smAT);
            printf("\n");
            print_matrix(smBT);     //印出 smBT
            append_list(&freelist, smBT);

            printf("\n");
            print_matrix(smS);      //印出 smS
            append_list(&freelist, smS);
            printf("\n");
            print_matrix(smM);      //印出 smM
            append_list(&freelist, smM);
            break;
        case 3:
            printf("\n");
            print_matrix(smA);     //印出 smA
            printf("\n");
            print_matrix(smB);     //印出 smB

            transpose_change_pointer(smA);
            transpose_change_pointer(smB);

            printf("\n");
            print_matrix(smA);     //印出 smAT
            printf("\n");
            print_matrix(smB);     //印出 smBT
            break;
        default:
            printf("ERROR: unable to identify print_mode\n");
    }

    append_list(&freelist, smA);
    append_list(&freelist, smB);
    remove_list(&freelist);
    return 0;
}