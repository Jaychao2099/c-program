# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAXCODE 10000

typedef struct node{
    char *password;
    char chart;
    int freq;
    struct node *left, *right;
}node;


void insert_minheap(node *heap, node var, int *size){
    int i = (*size)++;
    while (i && var.freq <= heap[(i - 1) / 2].freq){   // 到 root 了 or 比不過了 => 跳出
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = var;
}

void adjust_min(node *data, int subroot_index, int size){
    node temp = data[subroot_index];             // 先暫存，之後放到正確位置
    int child = 2 * subroot_index + 1;
    while(child < size){            // 還有child
        if (child + 1 < size && data[child].freq > data[child + 1].freq) child++; // 變right child
        if (temp.freq <= data[child].freq) break;         // 比完了
        data[subroot_index] = data[child];      // 沒比贏，下面換上來
        subroot_index = child;                  // 更新 subroot_index
        child = 2 * subroot_index + 1;          // to left child
    }
    data[(child-1) / 2] = temp;     // while loop最後，child多下一層，現在返回
}

void create_heap_bottom_up(node *data, int size){
    for (int i = size/2 - 1; i > -1; i--){     // 先到最後一個parent
        adjust_min(data, i, size);
    }
}

node *delete_heap(node *heap, int *size){
    node *x = malloc(sizeof(node));
    // memcpy(x, &heap[0], sizeof(node));
    *x = heap[0];   // 返回值
    heap[0] = heap[--(*size)];
    adjust_min(heap, 0, *size);
    return x;
}

node *build_queue(char *m, int *size){
    node *queue = calloc(*size, sizeof(node));
    int *temp_freq = calloc('~' + 1, sizeof(int));
    for (int i = 0; i < (*size); i++){               // O(N)
        if (m[i] > '~' || m[i] < ' '){
            printf("ERROR: including invalid char '%c'", m[i]);
            exit(1);
        }
        temp_freq[(int)m[i]]++;
    }
    *size = 0;
    for (int i = ' '; i <= '~'; i++){                // O(1)
        if (temp_freq[i]){
            queue[*size].chart = (char)i;
            queue[*size].freq = temp_freq[i];
            // printf("queue[%d] = (%c, %d)\n", *size, queue[*size].chart, queue[*size].freq);  // ok
            // queue[*size].left = queue[*size].right = NULL;
            (*size)++;
        }
    }
    for (int i = 0; i <= *size; i++){                 // O(1)
        queue[i].password = calloc(*size, sizeof(char));
    }
    create_heap_bottom_up(queue, *size);             // O(N)
    // printf("queue size = %d\n", *size);
    free(temp_freq);
    return queue;
}

void Huffman(node *queue, int size){
    int ori_size = size;
    for (int i = 0; i < ori_size - 1; i++){                 // O(N log N)
        node t;
        t.left = delete_heap(queue, &size);
        t.right = delete_heap(queue, &size);
        
        t.freq = t.left->freq + t.right->freq;
        t.chart = '\0';
        t.password = calloc(ori_size, sizeof(char));
        insert_minheap(queue, t, &size);
    }
}

int inorder_iter(node *h_tree, int leaf_size, char **table){
    int password_length = 0;
    printf("leaf = %d\n", leaf_size);
    node **stack = calloc((leaf_size * 2 - 1), sizeof(node *));     // 所有node數
    int top = -1;

    node *current = h_tree;
    while (1){
        node *prev = current;
        while (current){
            stack[++top] = current;
            prev = current;
            current = current->left;            // L
            if (current){
                strcpy(current->password, prev->password);
                int last = strchr(current->password, '\0') - current->password;
                current->password[last] = '0';
                current->password[last+1] = '\0';
            }
        }

        if (top > -1){
            if (prev && prev->chart){
                table[(int)prev->chart] = prev->password;   // 建立對照表
                password_length += (strlen(prev->password) * prev->freq);     // 加總密碼長度
            }
            current = stack[top--];
            prev = current;
            current = current->right;           // R
            if (current){
                strcpy(current->password, prev->password);
                int last = strchr(current->password, '\0') - current->password;
                current->password[last] = '1';
                current->password[last+1] = '\0';
            }
        }
        else break;
    }
    free(stack);
    return password_length;
}

char *encoding(node *h_tree_root, int size, char **table, char *message){
    for (int i = ' '; i <= '~'; i++){
        table[i] = calloc(size, sizeof(char));  // 存 對應password，最後含'\0'
    }

    int length = inorder_iter(h_tree_root, size, table);     // 密碼長度、建立table

    char *encode = calloc(length + 1, sizeof(char));        // 密碼本身
    for (int i = 0; message[i]; i++){
        strcat(encode, table[(int)message[i]]);
    }
    return encode;
}

char *decoding(char *encode, node *h_tree){
    char *decode = malloc(MAXCODE *sizeof(char));
    int last = 0;
    node *current = h_tree;
    for (int i = 0; encode[i]; i++){
        switch (encode[i]){
        case '0':
            current = current->left;
            break;
        case '1':
            current = current->right;
            break;
        }
        if (!current->left){
            decode[last++] = current->chart;
            current = h_tree;
        }
    }
    decode[last] = '\0';
    return decode;
}

int main(){ 
    char message[] = "Trump Media & Technology Group stock (DJT) extended its massive rally early on Tuesday, rising as much as 11% in premarket trading as investors bet on former President Donald Trump's improved odds of winning the November election.";
    int size = strlen(message);
    printf("Message = %s\n", message);

    node *queue = build_queue(message, &size);      // size 變 char num = tree leaf num

    Huffman(queue, size);
    node *h_tree = &queue[0]; // Huffman 樹的根節點

    char **table = malloc(('~' + 1) * sizeof(char*));
    char *encode = encoding(h_tree, size, table, message);

    for (int i = ' '; i <= '~'; i++){
        if (table[i][0]){
            printf("%c = %s\n", (char)i, table[i]);
            free(table[i]);  // 釋放每個字符的編碼
        }
    }
    printf("Encode = %s\n", encode);

    char *decode = decoding(encode, h_tree);
    printf("Decode = %s\n", decode);

    free(table);
    free(queue);
    free(encode);
    free(decode);
    return 0;
}