# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct node{
    int data;
    struct node *parent;
    struct node *l_child;
    struct node *r_child;
    int height;     // 起始高度為 1
}node;

node *create_node(int x, node *parent){
    node *new = calloc(1, sizeof(node));
    new->data = x;
    new->parent = parent;
    new->height = 1;
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

void update_height(node *root){
    while (root){
        root->height = 1;
        int temp = max(root->l_child->height, root->r_child->height) + 1;
        root->height = max(root->height, temp);
        root = root->parent;
    }
}

void rotate_LL(node *x){
    node *p = x->parent;
    node *c = c->l_child;
    x->parent = p->parent;
    if (p->parent){
        if (p->parent->l_child == p)
            p->parent->l_child = x;
        else p->parent->r_child = x;
        x->parent = p->parent;
    }
    if (x->r_child){
        p->l_child = x->r_child;
        p->l_child->parent = p;
    }
    x->r_child = p;
    p->parent = x;
    update_height(p);
}

void rotate_RR(node *x){
    node *p = x->parent;
    node *c = c->r_child;
    x->parent = p->parent;
    if (p->parent){
        if (p->parent->l_child == p)
            p->parent->l_child = x;
        else p->parent->r_child = x;
        x->parent = p->parent;
    }
    if (x->l_child){
        p->r_child = x->l_child;
        p->r_child->parent = p;
    }
    x->l_child = p;
    p->parent = x;
    update_height(p);
}

void rotate_LR(node *x){
    rotate_RR(x->l_child);
    rotate_LL(x);
}

void rotate_RL(node *x){
    rotate_LL(x->r_child);
    rotate_RR(x);
}

_Bool legel_balance(node *x){
    return abs(x->l_child->height - x->r_child->height) <= 1;
}

void rotate(node *x){
    while (x->parent && legel_balance(x->parent)) x = x->parent;
    node *p = x->parent;
    node *gp = p->parent;
    if (x == p->l_child && p == gp->l_child) rotate_LL(x->parent);
    else if (x == p->r_child && p == gp->r_child) rotate_RR(x->parent);
    else if (x == p->l_child && p == gp->r_child) rotate_LR(x->parent);
    else rotate_RL(x->parent);
}

node *insert(node *root, int x){
    if (!root) return create_node(x, NULL);
    while (1){
        if (x == root->data) return root;   // 若已存在該值，直接回傳該節點
        root->height++;
        node **child;
        if (x < root->data) child = &root->l_child; // 決定要插入左子樹或右子樹
        else child = &root->r_child;

        if (!*child){       // 若該子節點不存在，則建立新節點
            *child = create_node(x, root);
            rotate(*child);
            return *child;
        }
        root = *child;      // 若該子節點存在，繼續往下找
    }
}

void replace_child(node *p, node *old_child, node *new_child){
    if (p->l_child == old_child) p->l_child = new_child;
    else p->r_child = new_child;
    if (new_child) new_child->parent = p;
    update_height(p);
}

void delete(node **root, int x){
    node *temp = search(*root, x);
    if (!temp) return;
    if (!temp->l_child || !temp->r_child){  // 只有一個子節點或無子節點
        node *child = temp->l_child ? temp->l_child : temp->r_child;
        if (temp->parent){  // 非根節點，更新父節點的子節點
            replace_child(temp->parent, temp, child);
            rotate(child);
            free(temp);
        } else {
            *root = child;  // 若刪除的是根節點，更新 root
            if (child) child->parent = NULL;
        }
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
    insert(root, 2);
    insert(root, 5);
    insert(root, 8);
    insert(root, 4);
    insert(root, 3);
    insert(root, 1);
    insert(root, 9);
    insert(root, 10);
    insert(root, 7);
    insert(root, 6);

    inorder(root);
    printf("\n");
    level_order(root);
    printf("\n");

    delete(&root, 5);
    delete(&root, 7);

    inorder(root);
    printf("\n");
    level_order(root);
    printf("\n");

    return 0;
}
