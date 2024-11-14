# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct{
    int *queue;
    int front, rear;
}Queue;

void radix_sort_LSD(int *list, int n, int max, int radix){
    int digits = (int)(log2(max) / log2(radix)) + 1;
    Queue *q = malloc(radix * sizeof(Queue));
    for (int i = 0; i < radix; i++){
        q[i].queue = malloc(n * sizeof(int));
        q[i].front = -1;
        q[i].rear = 0;
    }
    int temp_radix = 1;
    for (int i = 0; i < digits; i++){
        for (int j = 0; j < n; j++){
            int k = (list[j]/temp_radix) % radix;
            q[k].queue[++q[k].front] = list[j];
        }
        temp_radix *= radix;

        int temp_i = 0;
        for (int k = 0; k < radix; k++){
            while (q[k].front >= q[k].rear){
                list[temp_i++] = q[k].queue[q[k].rear++];
            }
            q[k].front = -1;
            q[k].rear = 0;
        }
    }

    for (int i = 0; i < digits; i++){
        free(q[i].queue);
    }
    free(q);
}

int main(){
    int count, max, radix;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    printf("Enter the MAX limit of list: ");
    scanf("%d", &max);

    printf("Enter the Radix: ");
    scanf("%d", &radix);

    int *list = malloc(count * sizeof(int));

    printf("Enter the list: ");
    for(int i = 0; i < count; i++){
        scanf("%d", &list[i]);
    }

    radix_sort_LSD(list, count, max, radix);

    printf("Sorted list:\n");
    for(int i = 0; i < count; i++){
        printf("%d ", list[i]);
    }

    free(list);

    return 0;
}