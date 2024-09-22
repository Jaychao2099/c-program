# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

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
        if (current->head == true){
            current = current->next;
        }
        else {
            current = current->right;
            printf("%s[%d] = ", m->name, i);
            printf("<%4d, %4d> = %4d\n", current->row, current->col, current->value);
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
    for (node *current_row = m->head_first->next; current_row != m->head_first; current_row = current_row->next){   // H0 起始
        printf("[");
        int zero_size = -1;
        node *current_col = current_row->right;
        do {     // 印出一 row
            zero_size = current_col->col - zero_size - 1;           // 與上一個元素的 col 差距
            for (int i = 0; i < zero_size; i++){
                printf("    0");
                if (i < m->head_first->col - 1)
                    printf(",");
            }
            if (current_col != current_row){
                printf("%4d", current_col->value);
                if (!current_col->head)
                    printf(",");
            }
            zero_size = current_col->value;
            current_col = current_col->right;
        } while (current_col != current_row->right);
        printf(" ]\n");
    }
}

Matrix input_sm(){}

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
    *newnode = (node){row, col, value, newnode, newnode, NULL, head};
    return newnode;
}

// append node
void append_node(Matrix *m, node *newnode, Matrix *freelist){
    // if m is empty, create head head node
    if (m->head_first == NULL){
        m->head_first = m->head_last = create_node(0, 0, 0, 1, freelist);
    }
    // append head node
    while (m->head_first->row < newnode->row + 1 || m->head_first->col < newnode->col + 1){
        node *new_head = create_node(0, 0, 0, 1, freelist);
        m->head_last->next = new_head;
        new_head->next = m->head_first;
        if (m->head_first->row < newnode->row + 1) m->head_first->row++;
        if (m->head_first->col < newnode->col + 1) m->head_first->col++;
    }
    // append entry node
    node *ptr_head = m->head_first;
    for (int i = 0; i <= newnode->row; i++) ptr_head = ptr_head->next;    // 指標指到該 row
    node **ptr_entry = &ptr_head;
    while ((*ptr_entry)->right != ptr_head)   // 指標指到該 row 最後一個元素
        ptr_entry = &(*ptr_entry)->right;
    newnode->right = ptr_head;
    (*ptr_entry)->right = newnode;      // 用 指標的指標 修改最後一個元素的 ->right 指向

    ptr_head = m->head_first;
    for (int i = 0; i <= newnode->col; i++) ptr_head = ptr_head->next;      // 指標指到該 col
    ptr_entry = &ptr_head;
    while ((*ptr_entry)->down != ptr_head)   // 指標指到該 col 最後一個元素
        ptr_entry = &(*ptr_entry)->down;
    newnode->down = ptr_head;
    (*ptr_entry)->down = newnode;      // 用 指標的指標 修改最後一個元素的 ->down 指向

    m->head_first->value++;     // 總 entry 增加
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
    }
    newlist->head_first = newlist->head_last = NULL;     // 讓 newlist 消失
}

// delete whole M
void remove_list(Matrix *M){
    node *next;
    for (;M->head_first != NULL; M->head_first = next){
        next = M->head_first->next;
        free(M->head_first);
    }
    M->head_last = NULL; 
}

int main(){
    int input_mode, print_mode;

    printf("Matrix transpose A^T\n");
    printf("Matrix transpose B^T\n");
    printf("Matrix Addition A + B = C\n");
    printf("Matrix Multiplication AB = D\n\n");
    while (1){
        printf("Input mode 1.user mode, 2.test mode (1/2): ");
        scanf("%d", &input_mode);
        if (input_mode == 1 || input_mode == 2) break;
        else printf("ERROR: invalid mode\n");
    }

    Matrix freelist = {NULL, NULL};
    Matrix smA = {NULL, NULL, "A"};
    Matrix smB = {NULL, NULL, "B"};

    switch (input_mode){
        case 1:
            smA = input_sm();
            smB = input_sm();
            break;
        case 2:
            append_node(&smA, create_node(0, 0,  15, 0, &freelist), &freelist);
            append_node(&smA, create_node(0, 3,  22, 0, &freelist), &freelist);
            append_node(&smA, create_node(0, 5, -15, 0, &freelist), &freelist);
            append_node(&smA, create_node(1, 1,  11, 0, &freelist), &freelist);
            append_node(&smA, create_node(1, 2,   3, 0, &freelist), &freelist);
            append_node(&smA, create_node(2, 3,  -6, 0, &freelist), &freelist);
            append_node(&smA, create_node(4, 0,  91, 0, &freelist), &freelist);
            append_node(&smA, create_node(5, 2,  28, 0, &freelist), &freelist);
            
            append_node(&smB, create_node(1, 0,  15, 0, &freelist), &freelist);
            append_node(&smB, create_node(1, 2,  -3, 0, &freelist), &freelist);
            append_node(&smB, create_node(2, 1,  11, 0, &freelist), &freelist);
            append_node(&smB, create_node(3, 1,   3, 0, &freelist), &freelist);
            append_node(&smB, create_node(3, 5,  28, 0, &freelist), &freelist);
            append_node(&smB, create_node(4, 0,  22, 0, &freelist), &freelist);
            append_node(&smB, create_node(4, 2,  -6, 0, &freelist), &freelist);
            append_node(&smB, create_node(5, 0, -15, 0, &freelist), &freelist);
            append_node(&smB, create_node(5, 1,  61, 0, &freelist), &freelist);
            append_node(&smB, create_node(5, 5,  17, 0, &freelist), &freelist);
            break;
        default:
            fprintf(stderr, "ERROR: unable to identify input_mode\n");
            return 1;
    }
    
    print_sm(&smA);
    printf("\n");
    print_sm(&smB);
    printf("\n");

    append_list(&freelist, &smA);
    append_list(&freelist, &smB);
    remove_list(&freelist);
    return 0;
}