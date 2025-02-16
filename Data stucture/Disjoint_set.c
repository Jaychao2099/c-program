# include <stdlib.h>
# include <stdio.h>

# define MAXSIZE 10

typedef struct node{
    int data;       // 可改成其他資料型態
    int parent;
}node;

void initialize_set(node **set){
    *set = (node*)malloc(MAXSIZE * sizeof(node));
    for (int i = 0; i < MAXSIZE; i++){
        (*set)[i].data = i;        // 可改成其他資料型態
        (*set)[i].parent = i;      // 一開始每個元素都是自己的parent
    }
}

int find(node *set, int x){        // O(ackermann(n)) ~= O(1)
    if (set[x].parent != x){
        set[x].parent = find(set, set[x].parent);   // collapsing find
    }
    return set[x].parent;       // 回傳root
}

void union_set(node *set, int x, int y){
    int root_x = find(set, x);
    int root_y = find(set, y);
    if (root_x != root_y){
        set[root_x].parent = root_y;
    }
}

void print_set(node *set){
    for (int i = 0; i < MAXSIZE; i++){
        printf("%d ", set[i].parent);
    }
    printf("\n");
}

int main(){
    node *set;
    initialize_set(&set);
    print_set(set);

    union_set(set, 1, 2);
    union_set(set, 3, 4);
    union_set(set, 5, 6);
    union_set(set, 6, 8);
    union_set(set, 4, 8);
    union_set(set, 7, 9);
    union_set(set, 0, 9);
    union_set(set, 0, 3);
    union_set(set, 0, 5);
    union_set(set, 0, 7);

    print_set(set);

    free(set);
    return 0;
}
