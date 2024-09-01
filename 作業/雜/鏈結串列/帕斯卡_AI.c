#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void printRow(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeRow(Node *head) {
    Node *current = head;
    Node *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void pascal(int layers) {
    if (layers <= 0) {
        printf("Please enter a positive number.\n");
        return;
    }

    Node *prevRow = NULL;
    
    for (int i = 1; i <= layers; i++) {
        Node *currentRow = createNode(1);
        Node *curr = currentRow;
        Node *prev = prevRow;

        for (int j = 1; j < i; j++) {
            int leftValue = (prev != NULL) ? prev->value : 0;
            int rightValue = (prev != NULL && prev->next != NULL) ? prev->next->value : 0;
            
            curr->next = createNode(leftValue + rightValue);
            curr = curr->next;
            if (prev != NULL) prev = prev->next;
        }

        printRow(currentRow);
        
        if (prevRow != NULL) {
            freeRow(prevRow);
        }
        prevRow = currentRow;
    }
    
    if (prevRow != NULL) {
        freeRow(prevRow);
    }
}

int main() {
    int layers;
    printf("How many layers? ");
    scanf("%d", &layers);
    pascal(layers);
    return 0;
}