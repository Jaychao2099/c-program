#include <stdio.h>
#include <stdlib.h>

#define node_num 10

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode_t;

static ListNode_t *delete_the_middle_node(ListNode_t *head) {
    if (!head->next) return NULL;
    
    ListNode_t **slow = &head;
    for (ListNode_t *fast = head; fast && fast->next; fast = fast->next->next) {    // fast 每次走兩步
        slow = &(*slow)->next;      // slow 每次走一步
    }
    
    ListNode_t *del = *slow;
    *slow = (*slow)->next;
    free(del);

    return head;
}

int main() {
    ListNode_t *head = NULL, **ptr = &head;
    for (int i = 1; i <= node_num; i++) {
        ListNode_t *new = malloc(sizeof(ListNode_t));
        new->val = i;
        new->next = NULL;
        *ptr = new;
        ptr = &(*ptr)->next;
    }

    for (ListNode_t *node = head; node; node = node->next) {
        printf("%d ", node->val);
    }
    printf("\n");

    for (int i = 0; i < node_num; i++) {
        head = delete_the_middle_node(head);
        for (ListNode_t *node = head; node; node = node->next) {
            printf("%d ", node->val);
        }
        printf("\n");
    }   

    return 0;
}