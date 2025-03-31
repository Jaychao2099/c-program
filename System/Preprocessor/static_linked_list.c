#include <stdio.h>
  
#define cons(x, y) (struct llist[]){x, y}

struct llist { int val; struct llist *next; };

int main() {
    struct llist *list = cons(9, cons(5, cons(4, cons(7, NULL))));
    
    struct llist *list = (struct llist[]){9, (struct llist[]){5, (struct llist[]){4, (struct llist[]){7, ((void *)0)}}}};

    struct llist *p = list;
    for (; p; p = p->next)
        printf("%d -> ", p->val);       
    printf("\n");
    return 0;
}
