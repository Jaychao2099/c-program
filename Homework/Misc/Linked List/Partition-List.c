#include <stdio.h>
#include <stdlib.h>

// 給定一個鏈結串列跟整數 x，將串列分割成兩組，比 x 小的節點置前，大於或等於 x 的節點置後，應維持分割前的順序
// [1, 4, 3, 2, 5, 2], x = 3
// 輸出 [1, 2, 2, 4, 3, 5]

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode_t;

static ListNode_t *partition(ListNode_t *head, int x) {
    ListNode_t *big_first = NULL;
    ListNode_t **small_last = &head, **big_last = &big_first;
    
    for (ListNode_t *node = head; node; node = node->next) {
        ListNode_t ***inderect_ptr = (node->val < x) ? (&small_last) : (&big_last); // 利用"指標的指標的指標"操作要修改的指標：小的節點list or 大的節點list
        **inderect_ptr = node;                      // 將當前節點接到對應的鏈結串列上
        *inderect_ptr = &(**inderect_ptr)->next;    // 將指標指向下一個節點
    }
	
    *small_last = big_first;        // 將小於 x 的鏈結串列接上大於等於 x 的鏈結串列
    *big_last = NULL;               // 將大於等於 x 的鏈結串列的最後一個節點的 next 設為 NULL
    return head;
}

static ListNode_t *new_node(int value) {
    ListNode_t *node = malloc(sizeof(ListNode_t));
    node->val = value, node->next = NULL;
    return node;
}

int main() {
    ListNode_t *head = NULL, **ptr = &head;
    int arr[] = {1, 4, 3, 2, 5, 2};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        *ptr = new_node(arr[i]);
        ptr = &(*ptr)->next;
    }

    head = partition(head, 3);
    
    for (ListNode_t *node = head; node; node = node->next) {
        printf("%d ", node->val);
    }
    printf("\n");
    
    return 0;
}
