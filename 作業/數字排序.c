# include <stdio.h>

int main(){
    int count;
    printf("Enter the number of list: ");
    scanf("%d", &count);

    int list[count], sorted[count];

    printf("Enter the list: ");
    for(int i = 0; i < count; i++){
        scanf("%d", &list[i]);
    }

    for (int j = 0; j < count; j++){
        for(int k = j; k < count-1; k++){
            list[j] = list[j] < list[k+1] ? list[j] : list[k+1];
        }
    }
    printf("Sorted list:");
    for(int i = 0; i < count; i++){
        printf(" %d", list[i]);
    }
    return 0;
}