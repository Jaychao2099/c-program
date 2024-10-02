# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define print_inorder_rec(a) do {printf("\"%s\" In-order:\t", a->name); _print_inorder_rec(a->root); printf("\n");} while (0)
# define print_preorder_rec(a) do {printf("\"%s\" pre-order:\t", a->name); _print_preorder_rec(a->root); printf("\n");} while (0)
# define print_postorder_rec(a) do {printf("\"%s\" post-order:\t", a->name); _print_postorder_rec(a->root); printf("\n");} while (0)

# define copy_tree(a, b, new_name)        \
do {                                      \
        b = malloc(sizeof(Tree));         \
        b->name = new_name;               \
        b->root = _copy_tree(a->root);    \
} while (0)

# define equal(a, b) _equal(a->root, b->root)
# define swap_node(a) _swap_node(a->root)
# define count_node(a) _count_node(a->root)
# define count_leaf(a) _count_leaf(a->root)
# define tree_height(a) _tree_height(a->root)
# define remove_tree_rec(a) _remove_tree_rec(a->root)

# define EXPRESSION "A - (B/C + (D%E*F) / G) * H > (x+1)*(x^2-2*x+1)"

typedef struct node{
    struct node *left;
    char data;
    struct node *right;
}node;

typedef struct{
    node *root;
    int count;
    char *name;
}Tree;

// LVR
void _print_inorder_rec(node *current){      // tree->root
    if (current){
        _print_inorder_rec(current->left);
        printf("%c", current->data);
        _print_inorder_rec(current->right);
    }
}

// VLR
void _print_preorder_rec(node *current){      // tree->root
    if (current){
        printf("%c", current->data);
        _print_preorder_rec(current->left);
        _print_preorder_rec(current->right);
    }
}

// LRV
void _print_postorder_rec(node *current){      // tree->root
    if (current){
        _print_postorder_rec(current->left);
        _print_postorder_rec(current->right);
        printf("%c", current->data);
    }
}

void print_inorder_iter(Tree *tree){
    printf("\"%s\" In-order:\t", tree->name);
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
            printf("%c", stack[top--]->data);  // V
            current = current->right;           // R
        }
        else break;
    }
    printf("\n");
    free(stack);
}

void print_preorder_iter(Tree *tree){
    printf("\"%s\" Pre-order:\t", tree->name);
    if (tree == NULL || tree->root == NULL){
        printf("(non)\n");
        return;
    }
    node **stack = malloc(tree->count * sizeof(node *));
    int top = -1;
    node *current = tree->root;
    while (1){
        while (current){
            printf("%c", current->data);   // V
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
    printf("\"%s\" Post-order:\t", tree->name);
    if (tree == NULL || tree->root == NULL){
        printf("(non)\n");
        return;
    }
    node **stack = malloc(tree->count * sizeof(node *));
    int top = -1;
    node *current = tree->root;

    node *lastVisited = NULL;
    while (current || top > -1){
        if (current){
            stack[++top] = current;
            current = current->left;            // L
        }
        else {
            node *peekNode = stack[top];
            if (peekNode->right && lastVisited != peekNode->right){
                current = peekNode->right;      // R
            }
            else {
                printf("%c", peekNode->data);  // V
                lastVisited = peekNode;
                top--;
            }
        }
    }
    printf("\n");
    free(stack);
}

void print_levelorder(Tree *tree){
    printf("\"%s\" Level-order:\t", tree->name);
    if (tree == NULL || tree->root == NULL){
        printf("(non)\n");
        return;
    }
    node **queue = malloc(tree->count * sizeof(node *));
    int front = 0, rear = -1;
    queue[++rear] = tree->root;
    while (rear >= front){      // queue 空 -> 結束
        if (queue[front]->left) queue[++rear] = queue[front]->left;     // 下一 level 左邊加入 queue
        if (queue[front]->right) queue[++rear] = queue[front]->right;   // 下一 level 右邊加入 queue
        if (queue[front])
            printf("%c", queue[front++]->data);        // 印出當前這 level，進入 queue 中的下一個 node
    }
    printf("\n");
    free(queue);
}

// 建立節點
node *create_node(char var){
    node *newnode = malloc(sizeof(node));    // 請求一個新空間
    if (newnode == NULL){
        printf("ERROR: unable to allocate required memory in create_node\n");
        exit(1);
    }
    newnode->data = var;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// 複製一棵樹
node *_copy_tree(node *orig_node){
    if (orig_node){
        node *temp = create_node(orig_node->data);
        temp->left = _copy_tree(orig_node->left);
        temp->right = _copy_tree(orig_node->right);
        return temp;
    }
    return NULL;
}

// 判斷兩樹是否相等
_Bool _equal(const node *a, const node *b){
    if (!a && !b) return 1;
    if (a && b &&
        (a->data == b->data) &&
        _equal(a->left, b->left) &&
        _equal(a->right, b->right))
        return 1;
    return 0;
}

// 左右互換
void _swap_node(node *x){
    if (x){
        _swap_node(x->left);
        _swap_node(x->right);
        node *temp = x->left;
        x->left = x->right;
        x->right = temp;
    }
}

// 計算 node 數量
int _count_node(node *x){
    if (x)
        return 1 + _count_node(x->left) + _count_node(x->right);
    return 0;
}

// 計算 leaf 數量
int _count_leaf(node *x){
    if (x){
        int l = _count_leaf(x->left);
        int r = _count_leaf(x->right);
        if (l + r > 0) return l + r;
        else return 1;      // 本身是 leaf
    }
    return 0;
}

// 計算高度
int _tree_height(node *x){
    if (x){
        int l = _tree_height(x->left);
        int r = _tree_height(x->right);
        return 1 + __max(l, r);
    }
    return 0;
}

// 釋放記憶體，post-order recursive 法
void _remove_tree_rec(node *current){      // tree->root
    if (current){
        _remove_tree_rec(current->left);
        _remove_tree_rec(current->right);
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

// 只能處理 二元運算子
Tree *input_tree(char *text, char *name){
    if (text == NULL){
        printf("ERROR: Input parameters cannot be NULL\n");
        return NULL;
    }

    int length = strlen(text);
    if (length == 0){
        printf("ERROR: Input expression cannot be empty\n");
        return NULL;
    }

    node **node_stack = malloc(length * sizeof(node *));
    char *op_stack = malloc(length * sizeof(char));
    if (node_stack == NULL || op_stack == NULL){
        printf("ERROR: Memory allocation failed\n");
        free(node_stack);
        free(op_stack);
        return NULL;
    }

    int node_top = -1, op_top = -1;
    Tree *tree = calloc(1, sizeof(Tree));
    if (tree == NULL){
        printf("ERROR: Tree structure memory allocation failed\n");
        free(node_stack);
        free(op_stack);
        return NULL;
    }

    int parentheses_count = 0;  // 用於檢查括號是否匹配

    for (int i = 0; i < length; i++){
        if (text[i] == ' ') continue;   // 跳過空格
        if (isOperand(text[i])){        // 處理 運算元，放進 node_stack
            node *new_node = create_node(text[i]);
            if (new_node == NULL){
                printf("ERROR: Unable to create new node\n");
                goto cleanup;
            }
            node_stack[++node_top] = new_node;
            tree->count++;
        } else if (text[i] == '('){    // 處理'('，放進 op_stack
            op_stack[++op_top] = text[i];
            parentheses_count++;
        } else if (text[i] == ')'){    // 處理')'
            parentheses_count--;
            if (parentheses_count < 0){     // 括號不匹配
                printf("ERROR: Mismatched '(' and ')'\n");
                goto cleanup;
            }
            while (op_top >= 0 && op_stack[op_top] != '('){     // 括號內的 (a_node + b_node) 組成二階tree，放進 node_stack
                if (node_top < 1){
                    printf("ERROR: Invalid expression format\n");
                    goto cleanup;
                }
                node *right = node_stack[node_top--];
                node *left = node_stack[node_top--];
                node *op_node = create_node(op_stack[op_top--]);
                if (op_node == NULL){
                    printf("ERROR: Unable to create operator node\n");
                    goto cleanup;
                }
                op_node->left = left;
                op_node->right = right;
                node_stack[++node_top] = op_node;
                tree->count++;
            }
            if (op_top >= 0 && op_stack[op_top] == '('){        // 最後彈出 '('
                op_top--;
            } else {
                printf("ERROR: Missing '('\n");
                goto cleanup;
            }
        } else if (strchr("!^*/%+-><", text[i])){               // 處理 運算子，node_stack 拿出 2 個 node，組成二階樹，放回 node_stack
            while (op_top >= 0 && priority(op_stack[op_top], "isp") <= priority(text[i], "icp")){
                if (node_top < 1){
                    printf("ERROR: Invalid expression format\n");
                    goto cleanup;
                }
                node *right = node_stack[node_top--];
                node *left = node_stack[node_top--];
                node *op_node = create_node(op_stack[op_top--]);
                if (op_node == NULL){
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

    if (parentheses_count != 0){        // 括號不匹配
        printf("ERROR: Mismatched parentheses\n");
        goto cleanup;
    }

    while (op_top >= 0){                // 處理剩餘的 運算子，node_stack 拿出 2 個 node，組成二階樹，放回 node_stack
        if (node_top < 1){
            printf("ERROR: Invalid expression format\n");
            goto cleanup;
        }
        node *right = node_stack[node_top--];
        node *left = node_stack[node_top--];
        node *op_node = create_node(op_stack[op_top--]);
        if (op_node == NULL){
            printf("ERROR: Unable to create operator node\n");
            goto cleanup;
        }
        op_node->left = left;
        op_node->right = right;
        node_stack[++node_top] = op_node;
        tree->count++;
    }

    if (node_top != 0){                 // 最後應只剩一個 node，就是 root
        printf("ERROR: Invalid expression format\n");
        goto cleanup;
    }

    tree->root = node_stack[0];
    free(node_stack);
    free(op_stack);
    tree->name = name;
    return tree;

cleanup:
    // 清理資源並返回 NULL
    while (node_top >= 0){
        _remove_tree_rec(node_stack[node_top--]);
    }
    free(node_stack);
    free(op_stack);
    free(tree);
    return NULL;
}


int main(){    
    Tree *a = input_tree(EXPRESSION, "a");

    Tree *b;
    copy_tree(a, b, "b");
    print_inorder_rec(a);
    print_inorder_rec(b);
    printf("%s and %s is %s\n", a->name, b->name, equal(a, b) ? "Equal" : "Not equal");

    swap_node(b);
    printf("After swap node:\n");
    print_inorder_rec(b);

    int count_b = count_node(b);    // to test count_node function
    printf("%s's count (%d) and %s's count (%d) is %s\n", a->name, a->count, b->name, count_b, a->count == count_b ? "Equal" : "Not equal");

    int leaf_a = count_leaf(a);
    int leaf_b = count_leaf(b);     // to test count_leaf function
    printf("%s's leaf (%d) and %s's leaf (%d) is %s\n", a->name, leaf_a, b->name, leaf_b, leaf_a == leaf_b ? "Equal" : "Not equal");

    int height_a = tree_height(a);
    int height_b = tree_height(b);  // to test tree_height function
    printf("%s's height (%d) and %s's height (%d) is %s\n", a->name, height_a, b->name, height_b, height_a == height_b ? "Equal" : "Not equal");

    remove_tree_rec(a);
    remove_tree_rec(b);
    free(a);
    free(b);

    return 0;
}