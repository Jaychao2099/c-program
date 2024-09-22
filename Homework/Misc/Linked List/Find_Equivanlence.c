# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

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
    bool visited;
    List list;
}Sequence;


typedef struct{
    int a;
    int b;
}Equivalence;

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

void find_equivalence(Equivalence *eq, int eq_size, Sequence *seq, int seq_size){
    for (int i = 0; i < eq_size; i++){
        append_node(&seq[eq[i].a].list, create_node(eq[i].b));
        append_node(&seq[eq[i].b].list, create_node(eq[i].a));
    }

    node **stack = malloc(seq_size * sizeof(node*));
    int top = -1;

    for (int i = 0; i < seq_size; i++){
        if (!seq[i].visited){
            printf("{%d", i);
            seq[i].visited = true;
            node *current = seq[i].list.head;
            while (current != NULL || top > -1){
                if (current != NULL && !seq[current->value].visited){
                    printf(", %d", current->value);
                    seq[current->value].visited = true;            // 準備跳過去的 list 標記為 1
                    stack[++top] = current->next;               // 此 list 下一格 push 進 stack
                    current = seq[current->value].list.head;    // 跳過去
                } else {
                    if (current == NULL && top > -1){                   // 此 list 沒有了, 但 stack 還有
                        current = stack[top--];
                    } else current = current ? current->next : NULL;    // 都沒了, 換下一個等價類
                }
            }
            printf("}\n");
        }
    }
    free(stack);
}

int main(){
    Equivalence eq[] = {{0, 4}, 
                         {3, 1},
                         {6, 10},
                         {8, 9},
                         {7, 4},
                         {6, 8},
                        //  {0, 2}, //
                         {3, 5},
                         {2, 11},
                         {11, 0}
                         };
    int eq_size = sizeof(eq) / sizeof(eq[0]);
    int max = 0;
    for (int i = 0; i < ARRAY_SIZE(eq); i++){
        max = MAX(max, MAX(eq[i].a, eq[i].b));
    }
    int seq_size = max + 1;
    Sequence *sequence = calloc(seq_size, sizeof(Sequence));
    
    find_equivalence(eq, eq_size, sequence, seq_size);

    for (int i = 0; i < seq_size; i++){
        remove_list(&sequence[i].list);
    }
    free(sequence);
    return 0;
}