# include <stdio.h>
# include <stdlib.h>
# include <string.h>

 typedef struct node{
     int data;
     struct node *left;
     struct node *right;
     int npl;   // null path length
 }node;

node *merge(node *h1, node *h2){
    if (!h1) return h2;    // 有一個是 NULL
    if (!h2) return h1;    // 有一個是 NULL
    if (h1->data < h2->data){       // 小的當root
        node *temp = h1;
        h1 = h2;
        h2 = temp;
    }
    h1->right = merge(h1->right, h2);                   // 右子樹繼續比大小
    if (!h1->left || h1->left->npl < h1->right->npl){   // swap if 右邊比較高
        node *temp = h1->left;
        h1->left = h1->right;
        h1->right = temp;
    }
    if (!h1->right) h1->npl = 0;
    else h1->npl = h1->right->npl + 1;
    return h1;
}

node *insert(node *h, int data){
    node *new = malloc(sizeof(node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    new->npl = 0;
    return merge(h, new);
}

node *delete(node *h){
    node *left = h->left;
    node *right = h->right;
    free(h);
    return merge(left, right);
}

void print_heap(node *h){
    if (!h) return;
    printf("%d ", h->data);
    print_heap(h->left);
    print_heap(h->right);
}

int main(){
    node *h = NULL;
    h = insert(h, 3);
    h = insert(h, 2);
    h = insert(h, 1);
    h = insert(h, 4);
    h = insert(h, 5);
    h = insert(h, 6);

    print_heap(h);
    printf("\n");
    
    h = delete(h);
    print_heap(h);
    
    return 0;
}
