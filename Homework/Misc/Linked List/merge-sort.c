#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node *next;
} node_t;

static node_t *mergeTwoLists(node_t *L1, node_t *L2) {
    node_t *head = NULL, **ptr = &head, **node;

    for (node = NULL; L1 && L2; *node = (*node)->next) {        // node 沿著 L1 或 L2 走
        node = (L1->val < L2->val) ? &L1: &L2;      // Choose the smaller value
        *ptr = *node;           // 將要合併節點更新到 head
        ptr = &(*ptr)->next;    // 將 ptr 指向 head->next 讓下一輪迴圈更新 head->next
    }
    *ptr = (node_t *)((uintptr_t) L1 | (uintptr_t) L2);     // 將剩下的節點接上去
    return head;
}

static node_t *mergesort_list(node_t *head) {
    if (!head || !head->next) return head;

    node_t *slow = head;
    for (node_t *fast = head->next; fast && fast->next; fast = fast->next->next)    // fast 每次走兩步、slow 每次走一步
        slow = slow->next;
    node_t *mid = slow->next;       // 找到中間的節點
    slow->next = NULL;              // 將鏈結串列分成兩半

    node_t *left = mergesort_list(head), *right = mergesort_list(mid);
    return mergeTwoLists(left, right);
}

static void mergesort(node_t **list) {
    *list = mergesort_list(*list);
}

int main() {
    node_t *head = NULL, **ptr = &head;
    for (int i = 0; i < 10; i++) {
        node_t *new = malloc(sizeof(node_t));
        new->val = rand() % 100;
        new->next = NULL;
        *ptr = new;
        ptr = &(*ptr)->next;
    }

    for (node_t *node = head; node; node = node->next) {
        printf("%d ", node->val);
    }
    printf("\n");

    mergesort(&head);

    for (node_t *node = head; node; node = node->next) {
        printf("%d ", node->val);
    }
    printf("\n");

    return 0;
}