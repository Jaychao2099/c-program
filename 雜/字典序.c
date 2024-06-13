#include<stdio.h>
#include<string.h>

void quicksort(char arr[][50], int left, int right) {
    int i = left, j = right;
    char pivot[50];
    strcpy(pivot, arr[(left + right) / 2]);
    char temp[50];

    // Partition
    while (i <= j) {
        while (strcmp(arr[i], pivot) < 0) {
            i++;
        }
        while (strcmp(arr[j], pivot) > 0) {
            j--;
        }
        if (i <= j) {
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
            i++;
            j--;
        }
    }

    // Recursion
    if (left < j) {
        quicksort(arr, left, j);
    }
    if (i < right) {
        quicksort(arr, i, right);
    }
}

int main() {
    int i;
    char str[10][50];

    printf("Enter 10 words:\n");

    for(i = 0; i < 10; ++i) {
        scanf("%s", str[i]);
    }

    quicksort(str, 0, 9);

    printf("\nAfter lexicographic order: \n");
    for(i = 0; i < 10; ++i) {
        puts(str[i]);
    }

    return 0;
}
