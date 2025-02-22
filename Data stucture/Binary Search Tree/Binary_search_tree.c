# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct node{
    int data;
    struct node *parent;
    struct node *l_child;
    struct node *r_child;
    // int left_size;
}node;

node *create_node(int x, node *parent){
    node *new = calloc(1, sizeof(node));
    new->data = x;
    new->parent = parent;
    return new;
}

node *search(node *root, int x){    
    while (root){
        if (x == root->data) return root;
        if (x < root->data) root = root->l_child;
        else root = root->r_child;
    }
    return NULL;
}

node *insert(node *root, int x){
    while (1){
        if (x == root->data) return root;
        if (x < root->data){
            if (!root->l_child){
                root->l_child = create_node(x, root);
                return root->l_child;
            }
            root = root->l_child;
        }
        else {
            if (!root->r_child){
                root->r_child = create_node(x, root);
                return root->r_child;
            }
            root = root->r_child;
        }
    }
}

void replace_child(node *parent, node *old_child, node *new_child){
    if (parent->l_child == old_child) parent->l_child = new_child;
    else parent->r_child = new_child;
    if (new_child) new_child->parent = parent;
}

void delete(node **root, int x){
    node *temp = search(*root, x);
    if (!temp) return;
    if (!temp->l_child || !temp->r_child){  // 只有一個子節點或無子節點
        node *child = temp->l_child ? temp->l_child : temp->r_child;
        if (temp->parent){
            replace_child(temp->parent, temp, child);
        } else {
            *root = child;  // 若刪除的是根節點，更新 root
            if (child) child->parent = NULL;
        }
        free(temp);
    } else { // 兩個子節點，找左子樹最大值 (或右子樹最小值)
        node *l_max = temp->l_child;
        while (l_max->r_child) l_max = l_max->r_child;
        temp->data = l_max->data;   // 用左子樹最大值覆蓋
        delete(&l_max, l_max->data);  // 遞迴刪除該節點
    }
}

void inorder(node *root){
    if (!root) return;
    inorder(root->l_child);
    printf("%d ", root->data);
    inorder(root->r_child);
}

void level_order(node *root){
    if (!root) return;
    node **queue = malloc(100 * sizeof(node *));
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear){
        node *current = queue[front++];
        printf("%d ", current->data);
        if (current->l_child) queue[rear++] = current->l_child;
        if (current->r_child) queue[rear++] = current->r_child;
    }
    free(queue);
}

int main(){
    node *root = create_node(10, NULL);
    insert(root, 5);
    insert(root, 15);
    insert(root, 3);
    insert(root, 7);
    insert(root, 12);
    insert(root, 17);
    insert(root, 1);
    insert(root, 4);
    insert(root, 6);
    insert(root, 8);
    insert(root, 11);
    insert(root, 13);
    insert(root, 16);
    insert(root, 18);

    inorder(root);
    printf("\n");
    level_order(root);
    printf("\n");

    delete(&root, 10);
    delete(&root, 15);

    inorder(root);
    printf("\n");
    level_order(root);
    printf("\n");

    return 0;
}
