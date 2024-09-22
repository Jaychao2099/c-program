# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define MaxTerms 100   //大陣列的最多容量

// 項 {coefficient, exponential}
typedef struct term{
    double coef;  //係數
    int exp;  //指數
}term;

// 多項式 {start index, end index, name of polynomial}
typedef struct polynomial{
    int start;  //每個多項式的 第一項 在哪個index
    int end;    //每個多項式的 最後一項 在哪個index
    char name;  //名稱
}polynomial;

// 全域變數 {total array, last(free) index, input_new_end var.}
typedef struct polynomial_system{
    term *termArray;    //全域 大陣列
    int free_index;     //全域 大陣列 最後一格留白
    int input_new_end;       // input時的全域變數
} polynomial_system;

// 初始化 polynomialSystem
polynomial_system init_polynomial_system(size_t size){
    polynomial_system ps;
    ps.termArray = (term *)calloc(size, sizeof(term));
    if (ps.termArray == NULL){
        fprintf(stderr, "ERROR: unable to allocate required memory");
        exit(1);
    }
    for (int i = 0; i < size - 1; i++) ps.termArray[i].exp = -1;    //初始化 exp = -1
    ps.free_index = 0;
    return ps;
}

void swap(term *v, int a, int b){
    if (a != b){
        term temp;
        temp = v[a];
        v[a] = v[b];
        v[b] = temp;
    }
}

//小到大排序
void q_sort(term *array_to_sort, int start_index, int end_index){
    while (start_index < end_index){
        int i = start_index;
        for (int j = start_index; j < end_index; j++){
            if(array_to_sort[j].exp < array_to_sort[end_index].exp){
                swap(array_to_sort, j, i);
                i++;
            }
        }
        swap(array_to_sort, end_index, i);

        if (i - start_index < end_index - i){
            q_sort(array_to_sort, start_index, i - 1);  //對較小的分區進行 遞迴調用
            start_index = i + 1;              //對較大的分區使用 while 迭代
        } else {
            q_sort(array_to_sort, i + 1, end_index);    //同上
            end_index = i - 1;
        }
    }
}

void reverse_array(term *array, int start_index, int end_index){
    while (start_index < end_index){   // 當 start 小於 end 時，繼續交換
        swap(array, start_index, end_index);    // 交換 start 和 end 指向的元素
        start_index++;    // 移動指標
        end_index--;
    }
}

void sort_by_exp(polynomial_system *ps, polynomial *x){
    int write = x->start;
    for (int read = x->start; read <= x->end; read++){
        if (ps->termArray[read].coef != 0){
            if (write != read){
                ps->termArray[write] = ps->termArray[read]; //非零項都往前移 覆蓋coef = 0的項
            }
            write++;    // 若 coef = 0, write就不動
        }
    }
    x->end = write - 1;
    ps->free_index = write;

    q_sort(ps->termArray, x->start, x->end);
    reverse_array(ps->termArray, x->start, x->end);
}

//印出多項式, mode 0 = 一般, 1 = 輸入時
void print_poly(polynomial_system *ps, polynomial x, int mode){
    printf("%c = ", x.name);
    for(int j = x.start; j <= x.end; j++){
        printf("%.2lf ", ps->termArray[j].coef);
        switch (ps->termArray[j].exp){      //指數為1 or 0時 可省略一些東西
            case -1: printf("x^"); break;   //指數為 -1 時 可繼續輸入
            case 0:  break;
            case 1:  printf("x"); break;
            default: printf("x^%d", ps->termArray[j].exp); break;
        }
        switch (mode){
            case 0:
                if (j == x.end)
                    printf("\n");
                else if (ps->termArray[j+1].coef < 0)
                    printf(" ");
                else
                    printf(" +");
                break;
            case 1:
                if (ps->termArray[j].exp != -1)        //exp = -1, 可繼續輸入 exp
                    if (j == ps->input_new_end)
                        printf("\n");
                    else if (ps->termArray[j+1].coef < 0)
                        printf(" ");
                    else
                        printf(" +");
                break;
            default:
                fprintf(stderr, "ERROR: unable to identify mode code\n");
                free(ps->termArray);
                exit(1);
        }
    }
}

polynomial input_poly(polynomial_system *ps, char name, int terms){    //輸入多項式
    polynomial x = {ps->free_index, ps->free_index - 1, name};
    printf("\n\"Polynomial %c\": ", name);
    printf("Enter coefficint and exponent 1-by-1:\n");
    printf("%c = ", x.name);
    ps->input_new_end = x.end + terms;
    for (int i = x.start; i <= ps->input_new_end; i++){
        ps->free_index++;
        x.end++;
        scanf("%lf", &ps->termArray[i].coef);   //輸入coef
        print_poly(ps, x, 1);      //隨時印出檢查
        scanf("%d", &ps->termArray[i].exp);     //輸入exp
        for (int j = x.start; j < i; j++){
            if (ps->termArray[i].exp == ps->termArray[j].exp){
                fprintf(stderr, "ERROR: same exp in different terms is not allowed\n");
                free(ps->termArray);
                exit(1);
            }
        }
        sort_by_exp(ps, &x);     //依 exp 排序
        print_poly(ps, x, 1);      //隨時印出檢查
    }
    if (ps->free_index != x.end + 1){
        fprintf(stderr, "ERROR: free_index error in input_poly\n");
        free(ps->termArray);
        exit(1);
    }
    return x;
}

// 新增一個 term
bool new_term(polynomial_system *ps, double c, int e){
    if (ps->free_index > MaxTerms){
        fprintf(stderr, "ERROR: too many terms in polynomials\n");
        free(ps->termArray);
        return false;
    }
    ps->termArray[ps->free_index].coef = c;
    ps->termArray[ps->free_index].exp = e;
    ps->free_index++;
    return true;
}

char compare_int(int a, int b){
    if (a == b) return '=';
    if (a < b) return '<';
    if (a > b) return '>';
}

polynomial poly_Add(polynomial_system *ps, polynomial A, polynomial B, char name){
    polynomial C = {ps->free_index, ps->free_index - 1, name};
    int current_a = A.start, current_b = B.start;   //用來歷遍的index
    double co;      //C 的係數
    while (current_a <= A.end && current_b <= B.end){   //歷遍A, B 的元素 至某一方元素用完
        switch (compare_int(ps->termArray[current_a].exp, ps->termArray[current_b].exp)){
            case '=':
                co = ps->termArray[current_a].coef + ps->termArray[current_b].coef;
                if (co){
                    if (new_term(ps, co, ps->termArray[current_a].exp)){
                        current_a++;
                        current_b++;
                        break;
                    } else exit(1);
                } else{
                    current_a++;
                    current_b++;
                    break;
                }
            case '>':
                if (new_term(ps, ps->termArray[current_a].coef, ps->termArray[current_a].exp)){
                    current_a++;
                    break;
                } else exit(1);
            case '<':
                if (new_term(ps, ps->termArray[current_b].coef, ps->termArray[current_b].exp)){
                    current_b++;
                    break;
                } else exit(1);
            default:
                fprintf(stderr, "ERROR: function poly_add went wrong\n");
                free(ps->termArray);
                exit(1);
        }
    }
    //歷遍A, B 剩餘的元素
    for (current_a; current_a <= A.end; current_a++)
        if (new_term(ps, ps->termArray[current_a].coef, ps->termArray[current_a].exp) == false)
            exit(1);
    for (current_b; current_b <= B.end; current_b++)
        if (new_term(ps, ps->termArray[current_b].coef, ps->termArray[current_b].exp) == false)
            exit(1);
    C.end = ps->free_index - 1;
    //printf("C.end = %d, free_index = %d\n", C.end, ps->free_index);
    sort_by_exp(ps, &C);     // 確保 C 依 exp 排序
    return C;
}

polynomial poly_Mult(polynomial_system *ps, polynomial A, polynomial B, char name){
    polynomial M = {ps->free_index, ps->free_index - 1, name};
    double co;      //M 的係數
    int ex;         //M 的指數
    for (size_t i = A.start; i <= A.end; i++){      //歷遍A, B 的元素
        for (size_t j = B.start; j <= B.end; j++){
            co = ps->termArray[i].coef * ps->termArray[j].coef;
            ex = ps->termArray[i].exp + ps->termArray[j].exp;
            if (co){
                int found = 0;
                for (size_t k = M.start; k <= M.end; k++){
                    if (ex == ps->termArray[k].exp){
                        ps->termArray[k].coef += co;        //指數相同的 係數相加
                        found = 1;
                        break;
                    }
                }
                if (!found){
                    if (new_term(ps, co, ex) == false) exit(1);
                    M.end++;
                }
            }
        }
    }
    sort_by_exp(ps, &M);     // 確保 M 依 exp 排序
    if (M.end != ps->free_index - 1){
        fprintf(stderr, "ERROR: free_index in poly_Mult\n");
        free(ps->termArray);
    }
    return M;
}

int main(){
    int terms_A, terms_B;       //項數
    
    printf("Polynomial addition C = A + B\n");
    printf("Polynomial multiplication D = A * B\n");
    printf("How many terms in A? ");
    scanf("%d", &terms_A);
    printf("How many terms in B? ");
    scanf("%d", &terms_B);
    if (terms_A + terms_B >= MaxTerms || terms_A < 0 || terms_B < 0){
        printf("Total terms must between 0 ~ %d", MaxTerms);
        return 1;
    }

    polynomial_system total_poly = init_polynomial_system(terms_A + terms_B + terms_A*terms_B + 1);
    if (total_poly.termArray == NULL){
        printf("ERROR: unable to allocate required memory\n");
        return 1;
    }

    polynomial poly_A = input_poly(&total_poly, 'A', terms_A);     //大陣列取得 poly_A 的資料
    polynomial poly_B = input_poly(&total_poly, 'B', terms_B);     //大陣列取得 poly_B 的資料

    polynomial poly_C = poly_Add(&total_poly, poly_A, poly_B, 'C');    //大陣列取得 poly_C 的資料
    polynomial poly_D = poly_Mult(&total_poly, poly_A, poly_B, 'D');    //大陣列取得 poly_C 的資料
    //printf("D.start = %d, D.end = %d, free_index = %d\n", poly_D.start, poly_D.end, total_poly.free_index);

    printf("\n");
    print_poly(&total_poly, poly_C, 0);     //印出 poly_C
    printf("\n");
    print_poly(&total_poly, poly_D, 0);     //印出 poly_D

    free(total_poly.termArray);

    return 0;
}