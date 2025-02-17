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

static inline void replace_child(node *parent, node *old_child, node *new_child){
    if (parent->l_child == old_child) parent->l_child = new_child;
    else parent->r_child = new_child;
    if (new_child) new_child->parent = parent;
}

void delete(node *root, int x){
    node *temp = search(root, x);
    while(1){
        if (!temp) return;
        if (!temp->l_child && !temp->r_child){
            replace_child(temp->parent, temp, NULL);
            free(temp);
            return;
        }
        if (temp->l_child && !temp->r_child){
            replace_child(temp->parent, temp, temp->l_child);
            free(temp);
            return;
        }
        if (!temp->l_child && temp->r_child){
            replace_child(temp->parent, temp, temp->r_child);
            free(temp);
            return;
        }
        node *l_max = temp->l_child;
        while (l_max->r_child) l_max = l_max->r_child;
        temp->data = l_max->data;
        temp = l_max;
    }
}

void inorder(node *root){
    if (!root) return;
    inorder(root->l_child);
    printf("%d ", root->data);
    inorder(root->r_child);
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

    delete(root, 10);

    inorder(root);
    printf("\n");

    return 0;
}
