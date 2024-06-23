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
    int i, count;
    printf("Enter the number of words: ");
    scanf("%d", &count);
    
    char str[count][50];

    printf("Enter %d words:\n", count);

    for(i = 0; i < count; ++i) {
        printf("%d: ", i + 1);
        scanf("%s", str[i]);
    }

    quicksort(str, 0, count - 1);

    printf("\nAfter lexicographic order: \n");
    for(i = 0; i < count; ++i) {
        printf("%d: %s\n", i + 1, str[i]);
    }
    puts("");
    return 0;
}


/*
#include<stdio.h>
#include <string.h>

int main()
{
    int i, j;
    char str[10][50], temp[50];

    printf("输入10个单词:\n");

    for(i=0; i<10; ++i) {
        scanf("%s",str[i]);
    }

    for(i=0; i<9; ++i) {
        for(j=i+1; j<10 ; ++j)
        {
            if(strcmp(str[i], str[j])>0)
            {
                strcpy(temp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }
        }
    }

    printf("\n排序后: \n");
    for(i=0; i<10; ++i)
    {
        puts(str[i]);
    }

    return 0;
}

*/