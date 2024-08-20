# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

int main(){
    int num, side;

    printf("How many side per dice? ");
    if (scanf("%d", &side) != 1 || side > 1000){
        printf("Error! Too large!");
        return 1;
    }
    
    printf("How many dice? ");
    scanf("%d", &num);

    srand(time(0));

    int dice;

    /*for (int i = 0; i < num; i++){
        dice = rand() % side + 1;
        printf("%d\n", dice);
    }*/

    int *result;
    result = (int *)calloc(side, sizeof(int));

    for (int i = 0; i < num; i++){
        dice = rand() % side;
        for(int j = 0; j < side; j++) if (j == dice) result[j]++;
    }
    double avg = (double)num / (double)side;
    for (int i = 0; i < side; i++){
        printf("%*d: %*d (%5.1lf %)\n", (int)log10(side)+1, i+1, (int)log10(avg)+1, result[i], ((result[i]/avg)-1)*100);
    }
    free(result);
    
    return 0;
}