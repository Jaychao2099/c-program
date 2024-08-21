# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define MAX_DICE 10
# define MAX_FACE 600

void rollDice_random(int dice, int time, int face, int *result) {
    for (int i = 0; i < time; i++) {
        int sum = 0;
        for (int j = 0; j < dice; j++) {
            sum += (rand() % face) + 1;
        }
        result[sum]++;
    }
}

void rollDice_theory(int diceLeft, int currentSum, int face, int *frequency, int *total){
    if (diceLeft == 0) {
        frequency[currentSum]++;
        total[0]++;
        return;
    }

    // 遍歷每個骰子的面數
    for (int i = 1; i <= face; i++) {
        rollDice_theory(diceLeft - 1, currentSum + i, face, frequency, total);
    }
}

int main(){
    int face_num, dice_num, d_time, total_theory[1] = {0};

    printf("How many face per dice? ");
    if (scanf("%d", &face_num) != 1 || face_num > MAX_FACE || face_num < 1){
        printf("Error! Too many face! Must between 1 and %d", MAX_FACE);
        return 1;
    }
    printf("How many dice? ");
    if (scanf("%d", &dice_num) != 1 || dice_num > MAX_DICE || dice_num < 1){
        printf("Error! Too many face! Must between 1 and %d", MAX_DICE);
        return 1;
    }
    printf("Dice how many times? ");
    scanf("%d", &d_time);

    srand(time(0));

    int *result = (int *)calloc(face_num * dice_num + 1, sizeof(int)); // 實際值
    if (result == NULL){
        fprintf(stderr, "Error: unable to allocate required memory\n");
        return 1;
    }
    rollDice_random(dice_num, d_time, face_num, result);

    int *freq = (int *)calloc(face_num * dice_num + 1, sizeof(int));  // 理論值
    if (freq == NULL){
        fprintf(stderr, "Error: unable to allocate required memory\n");
        return 1;
    }
    rollDice_theory(dice_num, 0, face_num, freq, total_theory);

    double avg;
    printf("Sum\tFrequency\tTheoretical value\tbias\n");
    for (int i = dice_num; i <= dice_num * face_num; i++){
        avg = (double)freq[i] * (double)d_time / total_theory[0];
        printf("%d\t%d\t\t%.0lf\t\t\t(%5.1lf %)\n", i, result[i], avg, ((result[i]/avg)-1)*100);
    }
    
    free(result);
    free(freq);
    
    return 0;
}