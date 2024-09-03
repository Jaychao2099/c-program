# include <stdio.h>
# include <stdlib.h>

# define MaxTerms 100   //大陣列的最多容量

typedef struct term{
    double coef;  //係數
    int exp;  //指數
}term;

typedef struct polynomial{
    int start;  //每個多項式的 第一項 在哪個index
    int end;    //每個多項式的 最後一項 在哪個index
    char name;  //名稱
}polynomial;

typedef struct polynomial_System{
    term *termArray;    //全域 大陣列
    int free_index;     //全域 大陣列 最後一格留白
} polynomial_System;

// 初始化 polynomialSystem
polynomial_System init_Polynomial_System(int size){
    polynomial_System ps;
    ps.termArray = (term *)calloc(size, sizeof(term));
    ps.free_index = 0;
    return ps;
}

void print_poly(polynomial_System *ps, polynomial x){          //印出多項式
    printf("%c = ", x.name);
    for(int j = x.start; j < x.end + 1; j++){
        printf("%.2lf ", ps->termArray[j].coef);
        switch (ps->termArray[j].exp){      //指數為1 or 0時 可省略一些東西
            case 0:  break;
            case 1:  printf("x"); break;
            default: printf("x^%d", ps->termArray[j].exp); break;
        }
        if (j != x.end) printf(" + ");
        else printf("\n");
    }
}

polynomial input_poly(polynomial_System *ps, char name, int terms){    //輸入多項式
    polynomial x = {ps->free_index, ps->free_index + terms - 1, name};
    printf("\n\"Polynomial %c\":\n", name);
    int temp = 0;
    for (int i = x.start; i <= x.end; i++){
        printf("Enter %d coefficint: ", i - x.start + 1);
        scanf("%lf", &ps->termArray[i].coef);
        printf("Enter %d exponent: ", i - x.start + 1);
        scanf("%d", &ps->termArray[i].exp);

        print_poly(ps, x);      //隨時印出檢查
    }
    ps->free_index = x.end + 1;
    return x;
}

void new_term(polynomial_System *ps, double c, int e){
    if (ps->free_index > MaxTerms){
        printf("ERROR: too many terms in polynomials\n");
        exit(1);
    }
    ps->termArray[ps->free_index].coef = c;
    ps->termArray[ps->free_index].exp = e;
    ps->free_index++;
}

char compare_int(int a, int b){
    if (a == b) return '=';
    if (a < b) return '<';
    if (a > b) return '>';
}

polynomial poly_Add(polynomial_System *ps, polynomial A, polynomial B){
    polynomial C = {ps->free_index, ps->free_index, 'C'};
    int current_a = A.start, current_b = B.start;   //用來歷遍的index
    double co;      //C 的係數

    while (current_a <= A.end && current_b <= B.end){   //歷遍A, B 的元素 至某一方元素用完
        switch (compare_int(ps->termArray[current_a].exp, ps->termArray[current_b].exp)){
            case '=':
                co = ps->termArray[current_a].coef + ps->termArray[current_b].coef;
                if (co) new_term(ps, co, ps->termArray[current_a].exp);
                current_a++;
                current_b++;
                break;
            case '>':
                new_term(ps, ps->termArray[current_a].coef, ps->termArray[current_a].exp);
                current_a++;
                break;
            case '<':
                new_term(ps, ps->termArray[current_b].coef, ps->termArray[current_b].exp);
                current_b++;
                break;
            default: printf("ERROR: function poly_add wrong\n"); exit(1);
                break;
        }
    }
    //歷遍A, B 剩餘的元素
    for (current_a; current_a <= A.end; current_a++)
        new_term(ps, ps->termArray[current_a].coef, ps->termArray[current_a].exp);
    for (current_b; current_b <= B.end; current_b++)
        new_term(ps, ps->termArray[current_b].coef, ps->termArray[current_b].exp);
    
    C.end = ps->free_index - 1;
    return C;
}

int main(){
    int terms_A, terms_B;       //項數
    
    printf("Polynomial addition (A)+(B) = (C)\n");
    printf("How many terms in A? ");
    scanf("%d", &terms_A);
    printf("How many terms in B? ");
    scanf("%d", &terms_B);
    if (terms_A + terms_B >= MaxTerms || terms_A < 0 || terms_B < 0){
        printf("Total terms must between 0 ~ %d", MaxTerms);
        return 1;
    }

    polynomial_System total_poly = init_Polynomial_System(terms_A + terms_B + 1);
    if (total_poly.termArray == NULL){
        printf("ERROR: unable to allocate required memory\n");
        return 1;
    }

    polynomial poly_A = input_poly(&total_poly, 'A', terms_A);     //大陣列取得 poly_A 的資料
    polynomial poly_B = input_poly(&total_poly, 'B', terms_B);     //大陣列取得 poly_B 的資料
    
    polynomial poly_C = poly_Add(&total_poly, poly_A, poly_B);    //大陣列取得 poly_C 的資料

    printf("\n");
    print_poly(&total_poly, poly_C);     //印出 poly_C

    free(total_poly.termArray);

    return 0;
}