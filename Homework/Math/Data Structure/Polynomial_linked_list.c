# include <stdio.h>
# include <stdlib.h>

typedef struct term{
    double coef;        // 係數
    int exp;            // 指數
    struct term *next;
}term;

typedef struct{
    term *head;
    term *last;
    char *name;
}List;

int print_list(List *list, int inputing){
    printf("%s = ", list->name);
    for (term *ptr = list->head; ptr; ptr = ptr->next){
        if (ptr->coef){
            printf("%.2lf ", ptr->coef);
            switch (ptr->exp){      // 指數為1 or 0時 可省略一些東西
                case 0:  printf(""); break;
                case 1:  printf("x"); break;
                default: printf("x^%d", ptr->exp); break;
            }
            if (ptr->next){
                if (ptr->next->coef < 0)
                    printf(" ");
                else
                    printf(" +");
            } else if (inputing)
                printf(" +");
            else
                printf("\n");
        }
    }
}

// create term
term *create_node(int co, double ex, List *freelist){
    term *newnode;
    if (freelist->head != NULL){                    // 可用 freelist 的空間
        newnode = freelist->head;                   // 用 freelist 的第一個空間
        freelist->head = freelist->head->next;
    }
    else {
        newnode = malloc(sizeof(term));    // 請求一個新空間
        if (newnode == NULL){
            printf("ERROR: unable to allocate required memory in create_node\n");
            exit(1);
        }
    }

    newnode->coef = co;
    newnode->exp = ex;
    newnode->next = NULL;
    return newnode;
}

// append term
void append_node(List *list, term *newnode){
    if (list->head == NULL){                      // list empty
        list->head = list->last = newnode;
        return;
    }
    list->last->next = newnode;
    list->last = newnode;
    newnode->next = NULL;
}

// insert term
// void insert_node(List *list, term *target, term *newnode){
//     term **ptr = &target;
//     if (target == NULL){
//         *ptr = newnode;
//         list->last = newnode;
//         return;
//     }
//     newnode->next = target->next;
//     target->next = newnode;
// }

// delete target term to freelist
// void remove_node(List *list, term *target, List *freelist){
//     term **ptr = &(list->head);
//     while (*ptr != target)      // (ptr 指向的 "term->next指標") 指向目標時 停止
//         ptr = &((*ptr)->next);  // &(*ptr)->next
//     *ptr = target->next;        // (指向 target 的 前一個 term->next) 改指向 target->next
//     if (list->last == target)   // if 剛好 target 是最後一個
//         list->last = *ptr;
//     append_node(freelist, target);  // 資源回收
// }

// concatenating list -> newlist
void append_list(List *list, List *newlist){
    if (list->head == NULL){
        list->head = newlist->head;
        list->last = newlist->last;
    }
    else {
        list->last->next = newlist->head;
        list->last = newlist->last;
    }
    newlist->head = newlist->last = NULL;     // 讓 newlist 消失
}

// insert after target
// void insert_list(List *list, term *target, List *newlist){
//     if (target->next == NULL){
//         list->last = newlist->last;
//         if (list->head == target)           // target == list->head == null
//             list->head = newlist->head;
//     }
//     newlist->last->next = target->next;
//     target->next = newlist->head;
//     newlist->head = newlist->last = NULL;   // 讓 newlist 消失
// }

// delete whole list
void remove_list(List *list){
    term *next;
    for (;list->head != NULL; list->head = next){
        next = list->head->next;
        free(list->head);
    }
    list->last = NULL; 
}

// inverting list
// void invert_list(List *list){
//     if (list->head == NULL) return;
//     term *current = list->head, *prev_1 = NULL, *prev_2;
//     list->last = list->head;
//     while (current != NULL){
//         prev_2 = prev_1;
//         prev_1 = current;
//         current = current->next;
//         prev_1->next = prev_2;
//     }
//     list->head = prev_1;
// }

List input_poly(char *name, List *freelist){
    List list = {NULL, NULL, name};
    printf("\nPolynomial %s: ", list.name);
    printf("Form: \"coef ('space') exp\", enter '0' to end:\n");
    printf("%s = ", list.name);
    term *ptr = list.head;
    int pre_e = INT_MAX;
    while (1) {
        double c;
        int e;
        scanf("%lf", &c);
        if (c == 0) break;
        scanf("%d", &e);
        if (e >= pre_e)
            printf("ERROR: Please enter exp in descending order\n");
        else {
            append_node(&list, create_node(c, e, freelist));
            print_list(&list, 1);
            pre_e = e;
        }
    }
    print_list(&list, 0);
    setbuf(stdin, '\0');    //清空 stdin
    return list;
}

char compare_int(int a, int b){
    if (a == b) return '=';
    if (a < b) return '<';
    if (a > b) return '>';
}

List poly_Add(List *a, List *b, char *name, List *freelist){
    List c = {NULL, NULL, name};
    term *current_a = a->head, *current_b = b->head;   //用來歷遍的index
    double co;      //C 的係數，之後計算
    while (current_a && current_b){   //歷遍A, B 的元素 至某一方元素用完
        switch (compare_int(current_a->exp, current_b->exp)){
            case '=':
                co = current_a->coef + current_b->coef;
                if (co)
                    append_node(&c, create_node(co, current_a->exp, freelist));
                current_a = current_a->next;
                current_b = current_b->next;
                break;
            case '>':
                if (current_a->coef)
                    append_node(&c, create_node(current_a->coef, current_a->exp, freelist));
                current_a = current_a->next;
                break;
            case '<':
                if (current_b->coef)
                    append_node(&c, create_node(current_b->coef, current_b->exp, freelist));
                current_b = current_b->next;
                break;
            default:
                fprintf(stderr, "ERROR: function poly_add went wrong\n");
                append_list(freelist, &c);
                List error = {NULL, NULL};
                return error;
        }
    }
    //歷遍A, B 剩餘的元素
    for (; current_a; current_a = current_a->next)
        if (current_a->coef){
            append_node(&c, create_node(current_a->coef, current_a->exp, freelist));
        }
    for (; current_b; current_b = current_b->next)
        if (current_b->coef){
            append_node(&c, create_node(current_b->coef, current_b->exp, freelist));
        }
    // sort_by_exp(ps, &C);     // 確保 C 依 exp 排序
    return c;
}

List poly_Mult(List *a, List *b, char *name, List *freelist){
    List m = {NULL, NULL, name};
    double co;      //m 的係數
    int ex;         //m 的指數
    for (term *current_a = a->head; current_a; current_a = current_a->next){      //歷遍A, B 的元素
        for (term *current_b = b->head; current_b; current_b = current_b->next){
            co = current_a->coef * current_b->coef;
            ex = current_a->exp + current_b->exp;
            if (co){
                int found = 0;
                for (term *current_m = m.head; current_m; current_m = current_m->next){
                    if (ex == current_m->exp){
                        current_m->coef += co;        //指數相同的 係數相加
                        found = 1;
                        break;
                    }
                }
                if (!found) append_node(&m, create_node(co, ex, freelist));
            }
        }
    }
    // sort_by_exp(ps, &m);     // 確保 m 依 exp 排序
    return m;
}

int main(){
    List freelist = {NULL, NULL};

    printf("Polynomial addition       A + B\n");
    printf("Polynomial multiplication A * B\n");

    List poly_a = input_poly("A", &freelist);     // 取得 poly_A 的資料
    List poly_b = input_poly("B", &freelist);     // 取得 poly_B 的資料
    
    List poly_c = poly_Add(&poly_a, &poly_b, "A+B", &freelist);    // 取得 poly_C 的資料
    if (poly_c.head){
        printf("\n");
        print_list(&poly_c, 0);     //印出 poly_C
        append_list(&freelist, &poly_c);
    }
    List poly_m = poly_Mult(&poly_a, &poly_b, "A*B", &freelist);   // 取得 poly_D 的資料
    if (poly_m.head){
        printf("\n");
        print_list(&poly_m, 0);     //印出 poly_D
        append_list(&freelist, &poly_m);
    }

    append_list(&freelist, &poly_a);
    append_list(&freelist, &poly_b);

    remove_list(&freelist);
    return 0;
}