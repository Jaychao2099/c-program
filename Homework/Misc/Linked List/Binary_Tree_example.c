# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define EXPRESSION "A+B*(C-D)/E"

typedef struct node{
    struct node *left;
    char value;
    struct node *right;
}node;

typedef struct{
    node *root;
    int count;
}Tree;

// LVR
void print_inorder_rec(node *current){      // tree->root
    if (current){
        print_inorder_rec(current->left);
        printf("%c", current->value);
        print_inorder_rec(current->right);
    }
}

// VLR
void print_preorder_rec(node *current){      // tree->root
    if (current){
        printf("%c", current->value);
        print_preorder_rec(current->left);
        print_preorder_rec(current->right);
    }
}

// LRV
void print_postorder_rec(node *current){      // tree->root
    if (current){
        print_postorder_rec(current->left);
        print_postorder_rec(current->right);
        printf("%c", current->value);
    }
}

void print_inorder_iter(Tree *tree){
    printf("In-order:\t");
    if (tree == NULL || tree->root == NULL){
        printf("(non)\n");
        return;
    }
    node **stack = malloc(tree->count * sizeof(node *));
    int top = -1;
    node *current = tree->root;
    while (1){
        while (current){
            stack[++top] = current;
            current = current->left;            // L
        }
        if (top > -1){
            current = stack[top];
            printf("%c", stack[top--]->value);  // V
            current = current->right;           // R
        }
        else break;
    }
    printf("\n");
    free(stack);
}

void print_preorder_iter(Tree *tree){
    printf("Pre-order:\t");
    if (tree == NULL || tree->root == NULL){
        printf("(non)\n");
        return;
    }
    node **stack = malloc(tree->count * sizeof(node *));
    int top = -1;
    node *current = tree->root;
    while (1){
        while (current){
            printf("%c", current->value);   // V
            stack[++top] = current;
            current = current->left;        // L
        }
        if (top > -1){
            current = stack[top--]->right;  // R
        }
        else break;
    }
    printf("\n");
    free(stack);
}

void print_postorder_iter(Tree *tree){
    printf("Post-order:\t");
    if (tree == NULL || tree->root == NULL){
        printf("(non)\n");
        return;
    }
    node **stack = malloc(tree->count * sizeof(node *));
    int top = -1;
    node *current = tree->root;

    node *lastVisited = NULL;
    while (current || top > -1){
        if (current) {
            stack[++top] = current;
            current = current->left;            // L
        }
        else {
            node *peekNode = stack[top];
            if (peekNode->right && lastVisited != peekNode->right){
                current = peekNode->right;      // R
            }
            else {
                printf("%c", peekNode->value);  // V
                lastVisited = peekNode;
                top--;
            }
        }
    }
    printf("\n");
    free(stack);
}

void print_levelorder(Tree *tree){
    printf("Level-order:\t");
    if (tree == NULL || tree->root == NULL){
        printf("(non)\n");
        return;
    }
    node **queue = malloc(tree->count * sizeof(node *));
    int front = 0, rear = -1;
    queue[++rear] = tree->root;
    while (rear - front >= 0){      // queue 空 -> 結束
        if (queue[front]->left) queue[++rear] = queue[front]->left;     // 下一 level 左邊加入 queue
        if (queue[front]->right) queue[++rear] = queue[front]->right;   // 下一 level 右邊加入 queue
        if (queue[front])
            printf("%c", queue[front++]->value);        // 印出當前這 level
    }
    printf("\n");
    free(queue);
}


node *create_node(char var, Tree *freelist){
    node *newnode;
    if (freelist->root){                    // 可用 freelist 的空間
        newnode = freelist->root;                   // 用 freelist 的第一個空間
        freelist->root = freelist->root->right;     // freelist 向右增長，似 stack
    }
    else {
        newnode = malloc(sizeof(node));    // 請求一個新空間
        if (newnode == NULL){
            printf("ERROR: unable to allocate required memory in create_node\n");
            exit(1);
        }
    }
    newnode->value = var;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// 釋放記憶體，post-order recursive 法
void remove_tree_rec(node *current){      // tree->root
    if (current){
        remove_tree_rec(current->left);
        remove_tree_rec(current->right);
        free(current);
    }
}

// 釋放記憶體，level-order iterative 法
void remove_tree_iter(Tree *tree){
    if (tree == NULL || tree->root == NULL){
        return;
    }
    node **queue = malloc(tree->count * sizeof(node *));
    int front = 0, rear = -1;
    queue[++rear] = tree->root;
    node *level_start = tree->root;
    while (rear - front >= 0){
        if (queue[front]->left) queue[++rear] = queue[front]->left;
        if (queue[front]->right) queue[++rear] = queue[front]->right;
        if (queue[front])
            free(queue[front++]);
    }
    printf("\n");
    free(queue);
}

int priority(const char x, char *mode){
    switch (x){
        case '!': return 1;
        case '^': return 2;
        case '*': case '/': case '%': return 3;
        case '+': case '-': return 4;
        case '>': case '<': return 5;
        case '(': return mode == "isp" ? 8 : 0;
        default:
            printf("\nERROR: invalid operator\n");
            exit(1);
    }
}

_Bool isOperand(const char x){
    return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z') || (x >= '0' && x <= '9');
}

Tree *input_tree(char *text, Tree *freelist) {
    if (text == NULL || freelist == NULL) {
        printf("ERROR: Input parameters cannot be NULL\n");
        return NULL;
    }

    int length = strlen(text);
    if (length == 0) {
        printf("ERROR: Input expression cannot be empty\n");
        return NULL;
    }

    node **node_stack = malloc(length * sizeof(node *));
    char *op_stack = malloc(length * sizeof(char));
    if (node_stack == NULL || op_stack == NULL) {
        printf("ERROR: Memory allocation failed\n");
        free(node_stack);
        free(op_stack);
        return NULL;
    }

    int node_top = -1, op_top = -1;
    Tree *tree = calloc(1, sizeof(Tree));
    if (tree == NULL) {
        printf("ERROR: Tree structure memory allocation failed\n");
        free(node_stack);
        free(op_stack);
        return NULL;
    }

    int parentheses_count = 0;  // 用於檢查括號是否匹配

    for (int i = 0; i < length; i++) {
        if (text[i] == ' ') continue;   // 跳過空格

        if (isOperand(text[i])) {       // 處理 運算元
            node *new_node = create_node(text[i], freelist);
            if (new_node == NULL) {
                printf("ERROR: Unable to create new node\n");
                goto cleanup;
            }
            node_stack[++node_top] = new_node;
            tree->count++;
        } else if (text[i] == '(') {    // 處理'('
            op_stack[++op_top] = text[i];
            parentheses_count++;
        } else if (text[i] == ')') {    // 處理')'
            parentheses_count--;
            if (parentheses_count < 0) {
                printf("ERROR: Mismatched '(' and ')'\n");
                goto cleanup;
            }
            while (op_top >= 0 && op_stack[op_top] != '(') {
                if (node_top < 1) {
                    printf("ERROR: Invalid expression format\n");
                    goto cleanup;
                }
                node *right = node_stack[node_top--];
                node *left = node_stack[node_top--];
                node *op_node = create_node(op_stack[op_top--], freelist);
                if (op_node == NULL) {
                    printf("ERROR: Unable to create operator node\n");
                    goto cleanup;
                }
                op_node->left = left;
                op_node->right = right;
                node_stack[++node_top] = op_node;
                tree->count++;
            }
            if (op_top >= 0 && op_stack[op_top] == '(') {
                op_top--;  // 彈出 '('
            } else {
                printf("ERROR: Missing '('\n");
                goto cleanup;
            }
        } else if (strchr("!^*/%+-><", text[i])) {  // 處理運算符
            while (op_top >= 0 && priority(op_stack[op_top], "isp") <= priority(text[i], "icp")) {
                if (node_top < 1) {
                    printf("ERROR: Invalid expression format\n");
                    goto cleanup;
                }
                node *right = node_stack[node_top--];
                node *left = node_stack[node_top--];
                node *op_node = create_node(op_stack[op_top--], freelist);
                if (op_node == NULL) {
                    printf("ERROR: Unable to create operator node\n");
                    goto cleanup;
                }
                op_node->left = left;
                op_node->right = right;
                node_stack[++node_top] = op_node;
                tree->count++;
            }
            op_stack[++op_top] = text[i];
        } else {
            printf("ERROR: Invalid character '%c'\n", text[i]);
            goto cleanup;
        }
    }

    if (parentheses_count != 0) {
        printf("ERROR: Mismatched parentheses\n");
        goto cleanup;
    }

    // 處理剩餘的運算符
    while (op_top >= 0) {
        if (node_top < 1) {
            printf("ERROR: Invalid expression format\n");
            goto cleanup;
        }
        node *right = node_stack[node_top--];
        node *left = node_stack[node_top--];
        node *op_node = create_node(op_stack[op_top--], freelist);
        if (op_node == NULL) {
            printf("ERROR: Unable to create operator node\n");
            goto cleanup;
        }
        op_node->left = left;
        op_node->right = right;
        node_stack[++node_top] = op_node;
        tree->count++;
    }

    if (node_top != 0) {
        printf("ERROR: Invalid expression format\n");
        goto cleanup;
    }

    tree->root = node_stack[0];
    free(node_stack);
    free(op_stack);
    return tree;

cleanup:
    // 清理資源並返回 NULL
    while (node_top >= 0) {
        remove_tree_rec(node_stack[node_top--]);
    }
    free(node_stack);
    free(op_stack);
    free(tree);
    return NULL;
}

int main(){
    Tree freelist = {NULL};

    printf("Input expression = %s\n", EXPRESSION);
    
    Tree *a = input_tree(EXPRESSION, &freelist);

    print_inorder_iter(a);
    print_preorder_iter(a);
    print_postorder_iter(a);
    print_levelorder(a);

    remove_tree_rec(a->root);
    free(a);

    return 0;
}