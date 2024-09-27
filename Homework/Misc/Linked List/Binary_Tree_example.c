# include <stdio.h>
# include <stdlib.h>

typedef struct node{
    struct node *left;
    char value;
    struct node *right;
}node;

typedef struct{
    node *root;
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

void print_inorder_iter(Tree *tree, int length){
    node **stack = malloc(length * sizeof(node *));
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

void print_preorder_iter(Tree *tree, int length){
    node **stack = malloc(length * sizeof(node *));
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

void print_postorder_iter(Tree *tree, int length){
    node **stack = malloc(length * sizeof(node *));
    int top = -1;
    node *current = tree->root;
    while (1){
        while (current){
            stack[++top] = current;
            current = current->left;
        }
        if (top > -1){
            while (top > -1 && current == stack[top]->right){
                current = stack[top--];
                printf("%c", current->value);
            }
            if (top > -1) current = stack[top]->right;
        }
        else break;
    }

    printf("\n");
    free(stack);
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

node *append_root_node(node *new_root, node *left_root, node *right_root){
    new_root->left = left_root;
    new_root->right = right_root;
    return new_root;
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

// 釋放記憶體，post-order iterative 法
void remove_tree_iter(node *current){      // tree->root
    
}

int main(){
    Tree freelist = {NULL};
    Tree *a = malloc(sizeof(Tree));
    a->root = create_node('A', &freelist);
    a->root = append_root_node(create_node('/', &freelist), a->root, create_node('B', &freelist));
    a->root = append_root_node(create_node('*', &freelist), a->root, create_node('C', &freelist));
    a->root = append_root_node(create_node('*', &freelist), a->root, create_node('D', &freelist));
    a->root = append_root_node(create_node('+', &freelist), a->root, create_node('E', &freelist));

    print_inorder_rec(a->root);
    printf("\n");
    print_inorder_iter(a, 9);

    print_preorder_rec(a->root);
    printf("\n");
    print_preorder_iter(a, 9);

    print_postorder_rec(a->root);
    printf("\n");
    print_postorder_iter(a, 9);

    remove_tree_rec(a->root);
    free(a);

    return 0;
}