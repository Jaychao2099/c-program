# include <stdio.h>
# include <stdlib.h>

typedef struct p_tree{     //結構體的標識符
    int value;      //代表值
    struct p_tree *left;    //左下
    struct p_tree *right;   //右下
    struct p_tree *next;    //右
}p_tree;           // typedef 創建的類型別名

void pascal(int layer){
    if (layer < 1){
        printf("Error: please enter positive number\n");
        return;
    }
    if (layer == 1){
        printf("1\n");
        return;
    }

    p_tree *head = calloc(1, sizeof(p_tree));   //建立頭節點
    head->value = 1;
    p_tree *current = head;
    p_tree *current_l = head->left = calloc(1, sizeof(p_tree));
    p_tree *current_r = head->right = calloc(1, sizeof(p_tree));
    head->next = NULL;

    p_tree *next_layer;
    for (int i = 2; i <= layer; i++){
        for (int j = 1; j <= i; j++){
            if (j == 1) next_layer = current_l; //記錄下一層位址

            current_l->value += current->value;
            current_r->value += current->value;

            current_l->next = current_r;
            current_r->next = (j == i ? NULL : (current->next->right = calloc(1, sizeof(p_tree)))); //最右邊，結束鏈結串列

            current_l->left = calloc(1, sizeof(p_tree));
            current_l->right = calloc(1, sizeof(p_tree));
            current_r->left = current_l->right;
            current_r->right = calloc(1, sizeof(p_tree));
            
            current = current->next;
            current_l = current_l->next;    //指到下一個節點
            current_r = current_r->next;    //指到下一個節點
        }
    }
    free(current_l);
    free(current_r);

    current = head;     //回頭節點
    for (int i = 1; i <= layer; i++){
        for (int j = 1; j <= i; j++){
            printf("%d", current->value);
            if (j == 1) next_layer = current->left;
            if (j == i){
                current = next_layer;
                printf("\n");
            }
            else{
                current = current->next;
                printf(" ");
            }
        }
    }
    free(current);
    free(next_layer);
}


int main(){
    int layers;
    
    printf("How many layers? ");
    scanf("%d", &layers);

    pascal(layers);

    return 0;
}