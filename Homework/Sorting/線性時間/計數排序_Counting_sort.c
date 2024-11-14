# include <stdio.h>
# include <stdlib.h>

void counting_sort(int *list, int n, int min, int max){
    int k = max - min + 1;
    
    int *array = calloc(k, sizeof(int));
    for (int i = 0; i < n; i++){
        array[list[i]-min]++;
    }
    
    int prev = 0, current = 0;
    for (int i = 0; i < k; i++){
        prev = current;
        current = array[i];
        if (i > 0) array[i] = prev + array[i-1];
        else array[0] = 0;
    }
    
    int *result = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        result[array[list[i] - min]++] = list[i];
    }

    for (int i = 0; i < n; i++){
        list[i] = result[i];
    }

    free(array);
    free(result);
}

int main(){
    int count, min, max;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    printf("Enter the range of list: (min max)");
    scanf("%d%d", &min, &max);

    int *list = malloc(count * sizeof(int));

    printf("Enter the list: ");
    for(int i = 0; i < count; i++){
        scanf("%d", &list[i]);
    }

    counting_sort(list, count, min, max);

    printf("Sorted list:\n");
    for(int i = 0; i < count; i++){
        printf("%d ", list[i]);
    }

    free(list);

    return 0;
}