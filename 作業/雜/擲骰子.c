# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main(){
    int num;

    printf("How many dice? ");
    scanf("%d", &num);

    srand(time(0));

    int dice;

    /*for (int i = 0; i < num; i++){
        dice = rand() % 6 + 1;
        printf("%d\n", dice);
    }*/

    int *result;
    result = (int *)calloc(6, sizeof(int));
    
    for (int i = 0; i < num; i++){
        dice = rand() % 6 + 1;
        switch (dice){
            case 1: result[0]++; break;
            case 2: result[1]++; break;
            case 3: result[2]++; break;
            case 4: result[3]++; break;
            case 5: result[4]++; break;
            case 6: result[5]++; break;
        }
    }
    for (int i = 0; i < 6; i++) printf("%d: %d\n", i+1, result[i]);

    free(result);
    
    return 0;
}