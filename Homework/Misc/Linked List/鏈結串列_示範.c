# include <stdio.h>
# include <stdlib.h>

typedef struct Person{   //結構體的標識符
    int value;  //年齡
    struct Person *next;
}Person;                 // typedef 創建的類型別名

int main(){
    int count, age;
    printf("How many members? ");
    scanf("%d", &count);

    Person *head = malloc(sizeof(Person)); //取得一個和 Person 大小一樣的區塊，然後被給 head 這個指標
    Person *current = head; //宣告現在只到哪裡的 current，先把它等於 head

    printf("Age of Person: ");
    for (int i = 0; i < count; i++){
        scanf("%d", &age);
        current->value = age;
        current->next = (i == count-1 ? NULL : malloc(sizeof(Person))); //建立節點完後，結束鏈結串列
        current = current->next;    //指到下一個節點
    }

    //以下準備把linked list裡面的東西都印出來
    current = head; //把current指回 head
    while (current != NULL){     //current為NULL的時候停下來
        printf("%d ", current->value);  //印目前的節點
        current = current->next;    //印完後要印下一個節點的內容
    }
    printf("\n");

    int find;
    printf("Age you want to delete: ");
    scanf("%d", &find); //要被刪掉的值

    Person *temp, *follow;
    temp = head;

    if (head == NULL) printf("Not found. \n");  //head為空的空鏈結

    if (head->value == find){ //第一個節點是要刪除的目標值
        head = head->next;
        free(temp);
    }

    while ((temp != NULL) && (temp->value != find)){ //尋找要刪除的目標
        follow = temp;
        temp = temp->next;
    }
    if (temp == NULL) printf("Not found. \n");
    else{
        follow->next = temp->next;  //跳過要刪除的目標
        free(temp);
    }

    //做完後再把結果印一遍出來
    printf("Age of Person: ");
    current = head; //把current指回 head
    while (current != NULL){     //current為NULL的時候停下來
        printf("%d ", current->value); //印目前的節點
        follow = current;
        current = current->next; //印完後要印下一個節點的內容
        free(follow);
    }
    printf("\n");

    return 0;
}