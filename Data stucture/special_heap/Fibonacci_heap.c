# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct node{
    int data;
    struct node *parent;
    struct node *child;   // first child
    struct node *sibling_next;   // next sibling
    struct node *sibling_prev;   // previous sibling
    int degree;  // number of children
    _Bool mark;  // 是否失去 child
}node;

typedef struct heap{
    node *min;  // pointer to the minimum node
    int n;      // number of nodes
}heap;

node *create_node(int data){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->sibling_next = new_node;
    new_node->sibling_prev = new_node;
    new_node->degree = 0;
    new_node->mark = 0;
    return new_node;
}

heap *create_heap(){
    heap *new_heap = (heap *)malloc(sizeof(heap));
    new_heap->min = NULL;
    new_heap->n = 0;
    return new_heap;
}

heap *merge(heap *h1, heap *h2){        // O(1)
    if(h1->min == NULL) return h2;
    if(h2->min == NULL) return h1;
    node *head = h1->min;
    node *tail = h2->min->sibling_prev;
    h1->min->sibling_prev->sibling_next = h2->min;
    h1->min->sibling_prev = h2->min->sibling_prev;
    h2->min->sibling_prev->sibling_next = h1->min;
    h2->min->sibling_prev = tail;
    if(h1->min->data > h2->min->data){
        h1->min = h2->min;
    }
    h1->n += h2->n;
    return h1;
}

heap *insert(heap *h, int data){        // O(1)
    heap *new_heap = create_heap();
    new_heap->min = create_node(data);
    new_heap->n = 1;
    return merge(h, new_heap);
}

void link(heap *h, node *y, node *x){   // O(1)
    y->sibling_prev->sibling_next = y->sibling_next;
    y->sibling_next->sibling_prev = y->sibling_prev;
    y->sibling_prev = y;
    y->sibling_next = y;
    y->parent = x;
    if(x->child == NULL){
        x->child = y;
    }
    else{
        y->sibling_next = x->child;
        y->sibling_prev = x->child->sibling_prev;
        x->child->sibling_prev->sibling_next = y;
        x->child->sibling_prev = y;
    }
    x->degree++;
    y->mark = 0;
}

void consolidate(heap *h){             // O(log n)
    int D = 1;
    int n = h->n;
    while((1 << D) <= n) D++;
    node *A[D];
    for(int i = 0; i < D; i++) A[i] = NULL;
    node *temp = h->min;
    do{
        node *x = temp;
        temp = temp->sibling_next;
        int d = x->degree;
        while(A[d] != NULL){
            node *y = A[d];
            if(x->data > y->data){
                node *temp = x;
                x = y;
                y = temp;
            }
            link(h, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }while(temp != h->min);
    h->min = NULL;
    for(int i = 0; i < D; i++){
        if(A[i] != NULL){
            if(h->min == NULL){
                h->min = A[i];
                h->min->sibling_next = h->min;
                h->min->sibling_prev = h->min;
            }
            else{
                h->min->sibling_prev->sibling_next = A[i];
                A[i]->sibling_prev = h->min->sibling_prev;
                h->min->sibling_prev = A[i];
                A[i]->sibling_next = h->min;
                if(A[i]->data < h->min->data){
                    h->min = A[i];
                }
            }
        }
    }
}

node *delete_min(heap *h){             // O(log n)
    node *min = h->min;
    if(min == NULL) return NULL;
    if(min->child != NULL){
        node *child = min->child;
        node *temp = child;
        do{
            temp->parent = NULL;
            temp = temp->sibling_next;
        }while(temp != child);
        h->min->sibling_prev->sibling_next = child;
        child->sibling_prev = h->min->sibling_prev;
        h->min->sibling_prev = temp->sibling_prev;
        temp->sibling_prev->sibling_next = h->min;
    }
    if(min->sibling_next == min){
        h->min = NULL;
    }
    else{
        h->min = min->sibling_next;
        consolidate(h);
    }
    h->n--;
    return min;
}

void cut(heap *h, node *x, node *y){   // O(1)
    if(x->sibling_next == x){
        y->child = NULL;
    }
    else{
        x->sibling_prev->sibling_next = x->sibling_next;
        x->sibling_next->sibling_prev = x->sibling_prev;
        if(y->child == x){
            y->child = x->sibling_next;
        }
    }
    y->degree--;
    x->sibling_prev = x;
    x->sibling_next = x;
    h->min->sibling_prev->sibling_next = x;
    x->sibling_prev = h->min->sibling_prev;
    h->min->sibling_prev = x;
    x->sibling_next = h->min;
    x->parent = NULL;
    x->mark = 0;
}

void cascading_cut(heap *h, node *y){   // O(log n)
    node *z = y->parent;
    if(z != NULL){
        if(y->mark == 0){
            y->mark = 1;
        }
        else{
            cut(h, y, z);
            cascading_cut(h, z);
        }
    }
}

heap *decrease_key(heap *h, node *x, int k){   // O(1)
    if(k > x->data){
        printf("ERROR: new key is greater than current key\n");
        return h;
    }
    x->data = k;
    node *y = x->parent;
    if(y != NULL && x->data < y->data){
        cut(h, x, y);
        cascading_cut(h, y);
    }
    if(x->data < h->min->data){
        h->min = x;
    }
    return h;
}

void print_heap(heap *h){
    if(h->min == NULL){
        printf("Heap is empty\n");
        return;
    }
    node *temp = h->min;
    do{
        printf("%d ", temp->data);
        temp = temp->sibling_next;
    }while(temp != h->min);
    printf("\n");
}

int main(){
    heap *h = create_heap();
    h = insert(h, 10);
    h = insert(h, 20);
    h = insert(h, 30);
    h = insert(h, 40);
    h = insert(h, 50);
    h = insert(h, 60);
    h = insert(h, 70);
    h = insert(h, 80);
    h = insert(h, 90);
    h = insert(h, 100);
    h = insert(h, 110);
    h = insert(h, 120);
    h = insert(h, 130);
    h = insert(h, 140);
    h = insert(h, 150);
    h = insert(h, 160);
    h = insert(h, 170);
    h = insert(h, 180);
    h = insert(h, 190);
    h = insert(h, 200);
    h = insert(h, 210);
    h = insert(h, 220);
    h = insert(h, 230);
    h = insert(h, 240);
    h = insert(h, 250);
    h = insert(h, 260);
    h = insert(h, 270);
    h = insert(h, 280);
    h = insert(h, 290);
    h = insert(h, 300);
    h = insert(h, 310);
    h = insert(h, 320);
    h = insert(h, 330);
    h = insert(h, 340);
    h = insert(h, 350);
    h = insert(h, 360);
    h = insert(h, 370);
    h = insert(h, 380);
    h = insert(h, 390);
    h = insert(h, 400);
    h = insert(h, 410);
    h = insert(h, 420);
    h = insert(h, 430);
    h = insert(h, 440);
    h = insert(h, 450);
    h = insert(h, 460);
    h = insert(h, 470);
    h = insert(h, 480);
    h = insert(h, 490);
    h = insert(h, 500);
    h = insert(h, 510);
    h = insert(h, 520);
    h = insert(h, 530);
    print_heap(h);
    node *min = delete_min(h);
    printf("min: %d\n", min->data);
    print_heap(h);
    return 0;
}