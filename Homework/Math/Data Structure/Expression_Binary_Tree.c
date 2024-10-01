#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define print_inorder_rec(a) do {printf("In-order:\t"); _print_inorder_rec(a->root); printf("\n");} while (0)
#define print_preorder_rec(a) do {printf("pre-order:\t"); _print_preorder_rec(a->root); printf("\n");} while (0)
#define print_postorder_rec(a) do {printf("post-order:\t"); _print_postorder_rec(a->root); printf("\n");} while(0)
#define remove_tree_rec(a) do {_remove_tree_rec(a->root);} while(0)

#define EXPRESSION "3+4*(5-2)/2"

typedef struct node {
    struct node *left;
    char data;
    double result;
    struct node *right;
} node;

typedef struct {
    node *root;
    int count;
} Tree;

void _print_inorder_rec(node *current) {
    if (current) {
        _print_inorder_rec(current->left);
        if (current->data)
            printf("%c", current->data);
        else
            printf("%.2f", current->result);
        _print_inorder_rec(current->right);
    }
}

void _print_preorder_rec(node *current) {
    if (current) {
        if (current->data)
            printf("%c", current->data);
        else
            printf("%.2f", current->result);
        _print_preorder_rec(current->left);
        _print_preorder_rec(current->right);
    }
}

void _print_postorder_rec(node *current) {
    if (current) {
        _print_postorder_rec(current->left);
        _print_postorder_rec(current->right);
        if (current->data)
            printf("%c", current->data);
        else
            printf("%.2f", current->result);
    }
}

void print_levelorder(Tree *tree) {
    printf("Level-order:\t");
    if (tree == NULL || tree->root == NULL) {
        printf("(non)\n");
        return;
    }
    node **queue = malloc(tree->count * sizeof(node *));
    int front = 0, rear = -1;
    queue[++rear] = tree->root;
    while (rear >= front) {      // queue 空 -> 結束
        node *current = queue[front++];
        if (current->left) queue[++rear] = current->left;     // 下一 level 左邊加入 queue
        if (current->right) queue[++rear] = current->right;   // 下一 level 右邊加入 queue
        
        if (current->data) {
            printf("%c ", current->data);        // 印出運算符
        } else {
            printf("%.2f ", current->result);    // 印出運算元（數字）
        }
    }
    printf("\n");
    free(queue);
}

node *create_node(char var, double value, Tree *freelist) {
    node *newnode;
    if (freelist->root) {
        newnode = freelist->root;
        freelist->root = freelist->root->right;
    }
    else {
        newnode = malloc(sizeof(node));
        if (newnode == NULL) {
            printf("ERROR: unable to allocate required memory in create_node\n");
            exit(1);
        }
    }
    newnode->data = var;
    newnode->result = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

void _remove_tree_rec(node *current) {
    if (current) {
        _remove_tree_rec(current->left);
        _remove_tree_rec(current->right);
        free(current);
    }
}

int priority(const char x, const char *mode) {
    switch (x) {
        case '!': return 1;
        case '^': return 2;
        case '*': case '/': case '%': return 3;
        case '+': case '-': return 4;
        case '>': case '<': return 5;
        case '(': return strcmp(mode, "isp") == 0 ? 8 : 0;
        default:
            printf("\nERROR: invalid operator\n");
            exit(1);
    }
}

// 解析數字
double parseNumber(const char *text, int *i) {
    char numStr[20] = {0};
    int j = 0;
    while (isdigit(text[*i]) || text[*i] == '.') {
        numStr[j++] = text[*i];
        (*i)++;
    }
    (*i)--;  // 回退一個字符，因為for循環會再次增加i
    return atof(numStr);
}

Tree *input_tree(const char *text, Tree *freelist) {
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

    int parentheses_count = 0;

    for (int i = 0; i < length; i++) {
        if (text[i] == ' ') continue;

        if (isdigit(text[i])) {
            double value = parseNumber(text, &i);
            node *new_node = create_node('\0', value, freelist);
            if (new_node == NULL) {
                printf("ERROR: Unable to create new node\n");
                goto cleanup;
            }
            node_stack[++node_top] = new_node;
            tree->count++;
        } else if (text[i] == '(') {
            op_stack[++op_top] = text[i];
            parentheses_count++;
        } else if (text[i] == ')') {
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
                node *op_node = create_node(op_stack[op_top--], 0, freelist);
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
                op_top--;
            } else {
                printf("ERROR: Missing '('\n");
                goto cleanup;
            }
        } else if (strchr("!^*/%+-><", text[i])) {
            while (op_top >= 0 && priority(op_stack[op_top], "isp") <= priority(text[i], "icp")) {
                if (node_top < 1) {
                    printf("ERROR: Invalid expression format\n");
                    goto cleanup;
                }
                node *right = node_stack[node_top--];
                node *left = node_stack[node_top--];
                node *op_node = create_node(op_stack[op_top--], 0, freelist);
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

    while (op_top >= 0) {
        if (node_top < 1) {
            printf("ERROR: Invalid expression format\n");
            goto cleanup;
        }
        node *right = node_stack[node_top--];
        node *left = node_stack[node_top--];
        node *op_node = create_node(op_stack[op_top--], 0, freelist);
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
    while (node_top >= 0) {
        _remove_tree_rec(node_stack[node_top--]);
    }
    free(node_stack);
    free(op_stack);
    free(tree);
    return NULL;
}

int main() {
    Tree freelist = {NULL};

    printf("Input expression = %s\n", EXPRESSION);
    
    Tree *a = input_tree(EXPRESSION, &freelist);

    print_inorder_rec(a);
    print_preorder_rec(a);
    print_postorder_rec(a);
    print_levelorder(a);

    remove_tree_rec(a);
    free(a);

    return 0;
}