# include <stdio.h>
# include <stdlib.h>

void shell_sort(int *list, int n){
	int i, j;
	int temp;
	for (int gap = n >> 1; gap > 0; gap >>= 1)
		for (i = gap; i < n; i++){
			temp = list[i];
			for (j = i - gap; j >= 0 && list[j] > temp; j -= gap){
				list[j + gap] = list[j];
            }
			list[j + gap] = temp;
		}
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

    shell_sort(list, count);

    printf("Sorted list:");
    for(int i = 0; i < count; i++){
        printf(" %d", list[i]);
    }
    
    free(list);

    return 0;
}