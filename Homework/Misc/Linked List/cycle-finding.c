#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node_t;

static inline Node_t *move(Node_t *cur) {
    return cur ? cur->next : NULL;
}


// cycle_length is cycle length
// meet_index is the meet node's index
// TAIL is the last node of the list except the cycle node
// length is the total number of the list node
static bool cycle_finding(Node_t *HEAD, Node_t **TAIL, int *length, int *meet_index, int *cycle_length) {
    Node_t *slow = move(HEAD);
    Node_t *fast = move(move(HEAD));

    // get meet point
    while (fast && slow && (fast != slow)) { 
        slow = move(slow);
        fast = move(move(fast));
    }

    // not loop
    if (!fast) {
        *TAIL = NULL;
        *meet_index = 0;
        *cycle_length = 0;
        *length = 0;
        for (slow = HEAD; slow; slow = move(slow))
            (*length)++;
        return false;
    }

    // get meet_index
    *meet_index = 0;
    slow = HEAD;
    while (slow != fast) {
        (*meet_index)++;
        slow = slow->next;
        fast = fast->next;
    }

    // get cycle_length
    *cycle_length = 1;
    slow = move(slow);
    *TAIL = slow;
    while (slow != fast) {
        *TAIL = slow;
        (*cycle_length)++;
        slow = move(slow);
    }
    *length = *meet_index + *cycle_length;

    return true;
}

static Node_t *new_node(int value) {
    Node_t *node = malloc(sizeof(Node_t));
    node->val = value, node->next = NULL;
    return node;
}

int main(){
    Node_t *head = NULL, **ptr = &head;
    int arr[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        *ptr = new_node(arr[i]);
        ptr = &(*ptr)->next;
    }

    // create a cycle
    *ptr = head->next->next; // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 3

    Node_t *tail;
    int length, meet_index, cycle_length;
    bool has_cycle = cycle_finding(head, &tail, &length, &meet_index, &cycle_length);

    printf("Has cycle: %s\n", has_cycle ? "true" : "false");
    printf("Length: %d\n", length);
    printf("meet_index: %d\n", meet_index);
    printf("cycle_length: %d\n", cycle_length);
    printf("Tail node value: %d\n", tail ? tail->val : -1);

    return 0;
}