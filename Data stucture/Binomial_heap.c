# include <stdio.h>
# include <stdlib.h>

typedef struct node{
    int data;
    int degree;
    struct node *child;
    struct node *sibling;
    struct node *parent;
}node;

node *create_node(int data){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->degree = 0;
    new_node->child = NULL;
    new_node->sibling = NULL;
    new_node->parent = NULL;
    return new_node;
}

node *merge(node *h1, node *h2){
    if(h1 == NULL) return h2;
    if(h2 == NULL) return h1;
    node *head = NULL;
    node *tail = NULL;
    node *temp1 = h1;
    node *temp2 = h2;
    while(temp1 != NULL && temp2 != NULL){
        if(temp1->degree <= temp2->degree){
            if(head == NULL){
                head = temp1;
                tail = temp1;
            }
            else{
                tail->sibling = temp1;
                tail = temp1;
            }
            temp1 = temp1->sibling;
        }
        else{
            if(head == NULL){
                head = temp2;
                tail = temp2;
            }
            else{
                tail->sibling = temp2;
                tail = temp2;
            }
            temp2 = temp2->sibling;
        }
    }
    if(temp1 != NULL){
        tail->sibling = temp1;
    }
    if(temp2 != NULL){
        tail->sibling = temp2;
    }
    return head;
}

node *union_heap(node *h1, node *h2){
    node *head = merge(h1, h2);
    if(head == NULL){
        return head;
    }
    node *prev = NULL;
    node *curr = head;
    node *next = curr->sibling;
    while(next != NULL){
        if(curr->degree != next->degree || (next->sibling != NULL && next->sibling->degree == curr->degree)){
            prev = curr;
            curr = next;
        }
        else{
            if(curr->data <= next->data){
                curr->sibling = next->sibling;
                next->parent = curr;
                next->sibling = curr->child;
                curr->child = next;
                curr->degree++;
            }
            else{
                if(prev == NULL){
                    head = next;
                }
                else{
                    prev->sibling = next;
                }
                curr->parent = next;
                curr->sibling = next->child;
                next->child = curr;
                next->degree++;
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return head;
}

node *insert(node *head, int data){
    node *new_node = create_node(data);
    return union_heap(head, new_node);
}

node *extract_min(node *head){
    if(head == NULL){
        return head;
    }
    node *prev = NULL;
    node *min = head;
    node *temp = head;
    node *prev_min = NULL;
    while(temp->sibling != NULL){
        if(temp->sibling->data < min->data){
            min = temp->sibling;
            prev_min = temp;
        }
        temp = temp->sibling;
    }
    if(prev_min == NULL){
        head = min->sibling;
    }
    else{
        prev_min->sibling = min->sibling;
    }
    node *child = min->child;
    node *temp1 = child;
    while(temp1 != NULL){
        temp1->parent = NULL;
        temp1 = temp1->sibling;
    }
    head = union_heap(head, child);
    return head;
}

void print_heap(node *head){
    if(head == NULL){
        return;
    }
    node *temp = head;
    while(temp != NULL){
        printf("%d ", temp->data);
        print_heap(temp->child);
        temp = temp->sibling;
    }
}

int main(){
    node *head = NULL;
    head = insert(head, 10);
    head = insert(head, 20);
    head = insert(head, 30);
    head = insert(head, 40);
    head = insert(head, 50);
    head = insert(head, 60);
    head = insert(head, 70);
    head = insert(head, 80);
    head = insert(head, 90);
    head = insert(head, 100);
    head = insert(head, 110);
    head = insert(head, 120);
    head = insert(head, 130);
    head = insert(head, 140);
    head = insert(head, 150);
    head = insert(head, 160);
    head = insert(head, 170);
    head = insert(head, 180);
    head = insert(head, 190);
    head = insert(head, 200);
    head = insert(head, 210);
    head = insert(head, 220);
    head = insert(head, 230);
    head = insert(head, 240);
    head = insert(head, 250);
    head = insert(head, 260);
    head = insert(head, 270);
    head = insert(head, 280);
    head = insert(head, 290);
    head = insert(head, 300);
    head = insert(head, 310);
    head = insert(head, 320);
    head = insert(head, 330);
    head = insert(head, 340);
    head = insert(head, 350);
    head = insert(head, 360);
    head = insert(head, 370);
    head = insert(head, 380);
    head = insert(head, 390);
    head = insert(head, 400);
    head = insert(head, 410);
    head = insert(head, 420);
    head = insert(head, 430);
    head = insert(head, 440);
    head = insert(head, 450);
    head = insert(head, 460);
    head = insert(head, 470);
    head = insert(head, 480);
    head = insert(head, 490);
    head = insert(head, 500);
    head = insert(head, 510);
    head = insert(head, 520);
    head = insert(head, 530);
    head = insert(head, 540);
    print_heap(head);
    printf("\n");
    head = extract_min(head);
    print_heap(head);
    printf("\n");
    head = extract_min(head);
    print_heap(head);
    printf("\n");
    head = extract_min(head);
    print_heap(head);
    printf("\n");

    return 0;
}