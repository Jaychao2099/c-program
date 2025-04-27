#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode_t;

static void remove_indirect(ListNode_t **head, int value) {
    ListNode_t **indirect = head;
    while (*indirect && (*indirect)->val != value) {
        indirect = &((*indirect)->next);
    }
    if (*indirect)
        *indirect = (*indirect)->next; // Remove the node from the list
}

static void append_indirect(int value, ListNode_t **head) {
    ListNode_t **indirect = head;

    ListNode_t *new = malloc(1 * sizeof(ListNode_t));
    new->val = value;
    new->next = NULL;

    while (*indirect)
        indirect = &((*indirect)->next);

    *indirect = new;
}

static ListNode_t *mergeTwoLists(ListNode_t *L1, ListNode_t *L2) {
    ListNode_t *head = NULL, **ptr = &head, **node;

    for (node = NULL; L1 && L2; *node = (*node)->next) {        // node 沿著 L1 或 L2 走
        node = (L1->val < L2->val) ? &L1: &L2;      // Choose the smaller value
        *ptr = *node;           // 將要合併節點更新到 head
        ptr = &(*ptr)->next;    // 將 ptr 指向 head->next 讓下一輪迴圈更新 head->next
    }
    *ptr = (ListNode_t *)((uintptr_t) L1 | (uintptr_t) L2);     // 將剩下的節點接上去
    return head;
}

static ListNode_t *mergeKLists(ListNode_t **lists, int listsSize) {
    if (!listsSize)
        return NULL;
    if (listsSize <= 1)
        return *lists;

    int m = listsSize >> 1;     // m = listsSize / 2
    ListNode_t *left = mergeKLists(lists, m);
    ListNode_t *right = mergeKLists(lists + m, listsSize - m);

    return mergeTwoLists(left, right);
}

int main() {
    ListNode_t *lists[3];
    for (int i = 0; i < 3; i++) {
        lists[i] = NULL;
        for (int j = 0; j < 5; j++) {
            append_indirect(i * 10 + j, &lists[i]);
        }
    }

    ListNode_t *mergedList = mergeKLists(lists, 3);

    for (ListNode_t *node = mergedList; node; node = node->next) {
        printf("%d ", node->val);
    }
    printf("\n");

    return 0;
}
