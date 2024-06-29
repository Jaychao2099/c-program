# include <stdio.h>

# define min(a, b) ((a) < (b) ? (a) : (b))

int main(){
    int count;
    scanf("Enter the number of list: %d", &count);
    int list[count], sorted[count];
    for(int i = 0; i < count; i++){
        scanf("%d", &list[i]);
    }

    for (int j = 0; j < count; j++){
        int smallest;
        for(int k = 0; k < count; k++){
            smallest = min(list[k], list[k+1]);
        }
        sorted[j] = smallest;
    }
    printf("Sorted list:");
    for(int i = 0; i < count; i++){
        printf(" %d", sorted[i]);
    }
    return 0;
}