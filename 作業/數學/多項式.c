# include <stdio.h>
# include <stdlib.h>

# define MaxTerms 100

typedef struct term{
    double coef;  //係數
    int exp;  //指數
}term;

typedef struct polynomial{
    int start;  //每個多項式的 第一項 在哪個index
    int end;    //每個多項式的 最後一項 在哪個index
    char name;  //名稱
}polynomial;

term *termArray;   //大陣列
int free_index = 0;       //大陣列 最後留白處

void print_poly(polynomial x){          //印出多項式
    printf("\n%c = ", x.name);
    for(int j = x.start; j < x.end + 1; j++){
        printf("%.2lf ", termArray[j].coef);
        switch (termArray[j].exp){      //指數為1 or 0時 可省略一些東西
            case 0:  break;
            case 1:  printf("x"); break;
            default: printf("x^%d", termArray[j].exp); break;
        }
        if (j != x.end) printf(" + ");
        else printf("\n");
    }
}

void scan_poly(polynomial x, int terms){    //輸入多項式
    printf("\n\"Polynomial %c\":\n", x.name);
    int temp = 0;
    for (int i = free_index; i < free_index + terms; i++){
        printf("Enter %d coefficint: ", i - free_index + 1);
        scanf("%lf", &termArray[i].coef);
        printf("Enter %d exponent: ", i - free_index + 1);
        scanf("%d", &termArray[i].exp);

        print_poly(x);      //隨時印出檢查
        temp++;
    }
    free_index += temp;
}

void new_term(double c, int e){
    termArray[free_index].coef = c;
    termArray[free_index].exp = e;
    free_index++;
}

char compare_int(int a, int b){
    if (a == b) return '=';
    if (a < b) return '<';
    if (a > b) return '>';
}

polynomial poly_Add(polynomial A, polynomial B){
    polynomial C;
    int a = A.start, b = B.start;   //用來歷遍的index
    C.start = free_index;
    double co;      //C 的係數

    while (a <= A.end && b <= B.end){   //歷遍A, B 的元素
        switch (compare_int(termArray[a].exp, termArray[b].exp)){
            case '=':
                co = termArray[a].coef + termArray[b].coef;
                if (co) new_term(co, termArray[a].exp);
                a++;
                b++;
                break;
            case '>':
                new_term(termArray[a].coef, termArray[a].exp);
                a++;
                break;
            case '<':
                new_term(termArray[b].coef, termArray[b].exp);
                b++;
                break;
            default: printf("ERROR: function poly_add wrong\n"); exit(1);
                break;
        }
    }
    //歷遍A, B 剩餘的元素
    for (a; a <= A.end; a++) new_term(termArray[a].coef, termArray[a].exp);
    for (b; b <= B.end; b++) new_term(termArray[b].coef, termArray[b].exp);
    
    C.end = free_index - 1;
    return C;
}

int main(){
    int terms_A, terms_B;       //項數
    polynomial poly_A, poly_B, poly_C;
    printf("Polynomial addition (A)+(B) = (C)\n");
    printf("How many terms in A? ");
    scanf("%d", &terms_A);
    printf("How many terms in B? ");
    scanf("%d", &terms_B);
    if (terms_A + terms_B > MaxTerms || terms_A < 0 || terms_B < 0){
        printf("Total terms must between 0 ~ %d", MaxTerms);
        return 1;
    }
    termArray = (term *)calloc(terms_A + terms_B + 1, sizeof(term));

    poly_A.start = 0;
    poly_A.end = terms_A - 1;
    poly_A.name = 'A';

    poly_B.start = terms_A;
    poly_B.end = terms_A + terms_B - 1;
    poly_B.name = 'B';

    poly_C.name = 'C';
    
    scan_poly(poly_A, terms_A);     //大陣列取得 poly_A 的資料
    scan_poly(poly_B, terms_B);     //大陣列取得 poly_B 的資料

    poly_C = poly_Add(poly_A, poly_B);  //大陣列取得 poly_C 的資料

    print_poly(poly_C);     //印出 poly_C

    free(termArray);

    return 0;
}