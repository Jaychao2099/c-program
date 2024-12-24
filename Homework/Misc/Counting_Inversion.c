# include <stdio.h>
# include <stdlib.h>

int merge_count(int *list, int *temp, int now_L, int end_L, int end_R){
    int now_R = end_L + 1;

    int now_temp = now_L;
    int count = end_R - now_L + 1;
    int result = 0;

    while (now_L <= end_L && now_R <= end_R){
        if (list[now_L] <= list[now_R]){
            temp[now_temp++] = list[now_L++];
        } else {
            temp[now_temp++] = list[now_R++];
            result += (end_L - now_L + 1);      // 左半剩餘數字 皆大於 右半的該數字
        }
    }
    while(now_L <= end_L) temp[now_temp++] = list[now_L++];
    while(now_R <= end_R) temp[now_temp++] = list[now_R++];

    for (int i = 0; i < count; i++, end_R--){
        list[end_R] = temp[end_R];
    }

    return result;
}

int sort_count(int *list, int *temp, int start, int end){
	if (start >= end) return 0;
    int center = (start + end) / 2;
    int s = sort_count(list, temp, start, center);
    int e = sort_count(list, temp, center+1, end);
    int c = merge_count(list, temp, start, center, end);
    return s + e + c;
}

int _counting_inversion(int *list, int n){
    int *temp = malloc(n * sizeof(int));
    int result = sort_count(list, temp, 0, n-1);
    free(temp);
    return result;
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

    printf("Inversion Count: %d\n", _counting_inversion(list, count));
    
    free(list);

    return 0;
}