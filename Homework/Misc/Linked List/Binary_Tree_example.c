# include <stdio.h>
# include <stdlib.h>

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
        printf("(non)");
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
        printf("(non)");
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
        printf("(non)");
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
        printf("(non)");
        return;
    }
    node **queue = malloc(tree->count * sizeof(node *));
    int front = 0, rear = -1;
    queue[++rear] = tree->root;
    node *level_start = tree->root;
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

void *append_root_node(Tree *tree, node *new_root, node *left_root, node *right_root){
    if (!new_root){
        printf("ERROR: invalid new root in append_root_node");
        exit(1);
    }
    if (left_root){
        new_root->left = left_root;
        tree->count++;
    }
    if (right_root){
        new_root->right = right_root;
        tree->count++;
    }
    tree->root = new_root;
}

// void append_tree(){}

// Tree *input_tree(char *text){
//     Tree *tree;
//     tree->root;
// }

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

int main(){
    Tree freelist = {NULL};
    Tree *a = calloc(1, sizeof(Tree));
    a->root = create_node('A', &freelist);
    append_root_node(a, create_node('/', &freelist), a->root, create_node('B', &freelist));
    append_root_node(a, create_node('*', &freelist), a->root, create_node('C', &freelist));
    append_root_node(a, create_node('*', &freelist), a->root, create_node('D', &freelist));
    append_root_node(a, create_node('+', &freelist), a->root, create_node('E', &freelist));

    // print_inorder_rec(a->root);
    // printf("\n");
    print_inorder_iter(a);

    // print_preorder_rec(a->root);
    // printf("\n");
    print_preorder_iter(a);

    // print_postorder_rec(a->root);
    // printf("\n");
    print_postorder_iter(a);

    print_levelorder(a);

    remove_tree_rec(a->root);
    free(a);

    return 0;
}