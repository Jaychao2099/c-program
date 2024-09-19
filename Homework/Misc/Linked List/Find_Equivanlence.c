# include <stdio.h>
# include <stdlib.h>

# define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
# define MAX(a, b) a > b ? a : b

typedef struct node{
    int value;
    struct node* next;
}node;

typedef struct{
    node *head;
    node *last;
}List;

typedef struct{
    int bool;
    List *list;
}Sequence;


typedef struct{
    int a;
    int b;
}Equivanlence;

// create node
node *create_node(int var){
    node *newnode;
    newnode = malloc(sizeof(node));    // 請求一個新空間
    if (newnode == NULL){
        printf("ERROR: unable to allocate required memory in create_node\n");
        exit(1);
    }

    newnode->value = var;
    newnode->next = NULL;
    return newnode;
}

// append node
void append_node(List *list, node *newnode){
    if (list->head == NULL){                      // list empty
        list->head = list->last = newnode;
        return;
    }
    list->last->next = newnode;
    list->last = newnode;
    newnode->next = NULL;
}

// delete whole list
void remove_list(List *list){
    node *next;
    for (;list->head != NULL; list->head = next){
        next = list->head->next;
        free(list->head);
    }
    list->last = NULL; 
}

void find_equivanlence(Equivanlence* eq, Sequence** seq){
    for (int i = 0; i < ARRAY_SIZE(eq); i++){
        seq[eq[i].a]->list->head = seq[eq[i].a]->list->last = NULL;
        seq[eq[i].b]->list->head = seq[eq[i].b]->list->last = NULL;
        append_node(seq[eq[i].a]->list, create_node(eq[i].b));
        append_node(seq[eq[i].b]->list, create_node(eq[i].a));
    }
    node **stack = malloc(ARRAY_SIZE(seq) * sizeof(node*));
    int top = -1;
    for (int i = 0; i < ARRAY_SIZE(seq); i++){
        if (seq[i]->bool == 0){
            printf("{%d, ", i);
            seq[i]->bool = 1;
            node *current = seq[i]->list->head;
            while (current != NULL || top > -1){
                if (seq[current->value]->bool == 0){
                    printf("%d, ", current->value);
                    stack[++top] = current;
                    current = seq[current->value]->list->head;
                    seq[current->value]->bool = 1;
                }
                else {
                    if (current->next == NULL){
                        current = stack[top--]->next;
                    }
                    else current = current->next;
                }
            }
            printf("}\n");
        }
    }
    free(stack);
}

int main(){
    Equivanlence eq[] = {{0, 4}, 
                          {3, 1},
                          {6, 10},
                          {8, 9},
                          {7, 4},
                          {6, 8},
                          {3, 5},
                          {2, 11},
                          {11, 0}};
    int max = 0;
    for (int i = 0; i < ARRAY_SIZE(eq); i++){
        max = MAX(max, MAX(eq[i].a, eq[i].b));
    }
    Sequence **sequence = calloc(max + 1, sizeof(Sequence));
    find_equivanlence(eq, sequence);
    for (int i = 0; i < max + 1; i++){
        remove_list(sequence[i]->list);
    }
    free(sequence);
    return 0;
}