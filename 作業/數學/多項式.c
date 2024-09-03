# include <stdio.h>
# include <stdlib.h>

# define MaxTerms 100

//struct term;
//struct polynomial;

typedef struct term{
    double coef;  //係數
    int exp;  //指數
    //struct polynomial poly;
}term;

term termArray[MaxTerms];   //大陣列
static int free_element = 0;       //最後留白

typedef struct polynomial{
    term *termArray;
    int free_element;
    int start, end; //每個多項式的第一項, 最後一項在哪個index
}polynomial;

