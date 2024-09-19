# include <stdio.h>
# include <stdlib.h>

typedef struct node{
    char value;
    struct node* next;
}node;

typedef struct{
    node *head;
    node *last;
}List;

void print_list(List *list){
    for (node *ptr = list->head; ptr != NULL; ptr = ptr->next)
        printf("%c ", ptr->value);
    printf("\n");
}

// create node
node *create_node(char var, List *freelist){
    node *newnode;
    if (freelist->head != NULL){                    // 可用 freelist 的空間
        newnode = freelist->head;                   // 用 freelist 的第一個空間
        freelist->head = freelist->head->next;
    }
    else {
        newnode = malloc(sizeof(node));    // 請求一個新空間
        if (newnode == NULL){
            printf("ERROR: unable to allocate required memory in create_node\n");
            exit(1);
        }
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

// insert node
void insert_node(List *list, node *target, node *newnode){
    node **ptr = &target;
    if (target == NULL){
        *ptr = newnode;
        list->last = newnode;
        return;
    }
    newnode->next = target->next;
    target->next = newnode;
}

// delete target node to freelist
void remove_node(List *list, node *target, List *freelist){
    node **ptr = &(list->head);
    while (*ptr != target)      // (ptr 指向的 "node->next指標") 指向目標時 停止
        ptr = &((*ptr)->next);  // &(*ptr)->next
    *ptr = target->next;        // (指向 target 的 前一個 node->next) 改指向 target->next
    if (list->last == target)   // if 剛好 target 是最後一個
        list->last = *ptr;
    append_node(freelist, target);  // 資源回收
}

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
void insert_list(List *list, node *target, List *newlist){
    if (target->next == NULL){
        list->last = newlist->last;
        if (list->head == target)           // target == list->head == null
            list->head = newlist->head;
    }
    newlist->last->next = target->next;
    target->next = newlist->head;
    newlist->head = newlist->last = NULL;   // 讓 newlist 消失
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

// inverting list
void invert_list(List *list){
    if (list->head == NULL) return;
    node *current = list->head, *prev_1 = NULL, *prev_2;
    list->last = list->head;
    while (current != NULL){
        prev_2 = prev_1;
        prev_1 = current;
        current = current->next;
        prev_1->next = prev_2;
    }
    list->head = prev_1;
}

int main(){
    List freelist = {NULL, NULL};
    List list_1 = {NULL, NULL};
    for(int i = 'A'; i <= 'J'; i++)
        append_node(&list_1, create_node(i, &freelist));
    
    printf("Original list: ");
    print_list(&list_1);

    invert_list(&list_1);
    printf("Inverted list: ");
    print_list(&list_1);

    List list_2 = {NULL, NULL};
    for(int i = '0'; i <= '9'; i++)
        append_node(&list_2, create_node(i, &freelist));
    append_list(&list_1, &list_2);
    printf("Appended list: ");
    print_list(&list_1);

    for(int i = '0'; i <= '9'; i++)
        append_node(&list_2, create_node(i, &freelist));
    insert_list(&list_1, list_1.head->next->next->next, &list_2);
    printf("Inserted list: ");
    print_list(&list_1);

    append_list(&freelist, &list_1);
    remove_list(&freelist);
    return 0;
}