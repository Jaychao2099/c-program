# include <stdio.h>
# include <stdlib.h>

void swap(char *v, int a, int b){
    if (a != b){
        char temp;
        temp = v[a];
        v[a] = v[b];
        v[b] = temp;
    }
}

void perm(char *list, int current, int last){
    if (current == last - 1) printf("%s\n", list);  //遞迴結束
    else {
        for (int j = current; j < last; j++){
            swap(list, current, j);             //換list[j]當頭
            perm(list, current + 1, last);      //排列剩餘元素
            swap(list, current, j);             //換回來
        }
    }
}

int main(){
    int num;

    printf("How many letters? ");
    scanf("%d", &num);

    char *input = (char *)malloc((num + 1) * sizeof(char));
    if (input == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter letters: ");
    scanf("%s", input);

    perm(input, 0, num);

    free(input);

    return 0;
}