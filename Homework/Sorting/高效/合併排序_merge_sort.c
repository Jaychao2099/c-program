# include <stdio.h>
# include <stdlib.h>

void merge(int *list, int *temp, int now_L, int end_L, int end_R){
    int now_R = end_L + 1;
    int now_temp = now_L;
    int count = end_R - now_L + 1;
    while (now_L <= end_L && now_R <= end_R){
        if (list[now_L] <= list[now_R]){
            temp[now_temp++] = list[now_L++];
        } else temp[now_temp++] = list[now_R++];
    }
    while(now_L <= end_L) temp[now_temp++] = list[now_L++];
    while(now_R <= end_R) temp[now_temp++] = list[now_R++];
    for (int i = 0; i < count; i++, end_R--){
        list[end_R] = temp[end_R];
    }
}

void merge_sort(int *list, int *temp, int start, int end){
	if (start >= end) return;
    int center = (start + end) / 2;
    merge_sort(list, temp, start, center);
    merge_sort(list, temp, center+1, end);
    merge(list, temp, start, center, end);
}

void _merge_sort(int *list, int n){
    int *temp = malloc(n * sizeof(int));
    merge_sort(list, temp, 0, n-1);
    free(temp);
}

int main(){
    int count;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    int *list = malloc(count * sizeof(int));

    printf("Enter the list: ");
    for(int i = 0; i < count; i++){
        scanf("%d", &list[i]);
    }

    _merge_sort(list, count);

    printf("Sorted list: ");
    for(int i = 0; i < count; i++){
        printf(" %d", list[i]);
    }
    
    free(list);

    return 0;
}