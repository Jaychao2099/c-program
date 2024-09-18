# include <stdio.h>
# include <stdlib.h>

typedef struct p_tree{
    int value;
    struct p_tree *next;
} p_tree;

void printRow(p_tree *head){
    p_tree *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeRow(p_tree *head){
    p_tree *current = head;
    p_tree *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

p_tree* createp_tree(int value){
    p_tree *newp_tree = (p_tree*)malloc(sizeof(p_tree));
    newp_tree->value = value;
    newp_tree->next = NULL;
    return newp_tree;
}

void pascal(int layers){
    if (layers <= 0) {
        printf("Please enter a positive number.\n");
        return;
    }

    p_tree *prevRow = NULL;
    
    for (int i = 1; i <= layers; i++){
        p_tree *currentRow = createp_tree(1);
        p_tree *curr = currentRow;
        p_tree *prev = prevRow;

        for (int j = 1; j < i; j++){
            int leftValue = (prev != NULL) ? prev->value : 0;
            int rightValue = (prev != NULL && prev->next != NULL) ? prev->next->value : 0;
            
            curr->next = createp_tree(leftValue + rightValue);
            curr = curr->next;
            if (prev != NULL) prev = prev->next;
        }

        printRow(currentRow);
        
        if (prevRow != NULL){
            freeRow(prevRow);
        }
        prevRow = currentRow;
    }
    
    if (prevRow != NULL) {
        freeRow(prevRow);
    }
}

int main(){
    int layers;
    printf("How many layers? ");
    scanf("%d", &layers);
    pascal(layers);
    return 0;
}