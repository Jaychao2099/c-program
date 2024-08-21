# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <limits.h>

# define MAX_DICE 10
# define MAX_FACE 600

// 取得使用者輸入並進行驗證
int getValidatedInput(const char *prompt, int min, int max){
    int value;
    printf("%s", prompt);
    if (scanf("%d", &value) != 1 || value < min || value > max) {
        printf("Error! Input must be between %d and %d\n", min, max);
        exit(1);
    }
    return value;
}

void rollDice_random(int dice, int time, int face, int *result){
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
    int face_num = getValidatedInput("How many face per dice? ", 1, MAX_FACE);
    int dice_num = getValidatedInput("How many dice? ", 1, MAX_DICE);
    int d_time = getValidatedInput("Dice how many times? ", 1, INT_MAX);

    srand(time(0));

    int *result = (int *)calloc(face_num * dice_num + 1, sizeof(int)); // 實際值
    if (result == NULL){
        free(result);
        fprintf(stderr, "Error: unable to allocate required memory\n");
        return 1;
    }
    rollDice_random(dice_num, d_time, face_num, result);

    int *freq = (int *)calloc(face_num * dice_num + 1, sizeof(int));  // 理論值
    if (freq == NULL){
        free(freq);
        fprintf(stderr, "Error: unable to allocate required memory\n");
        return 1;
    }
    int total_theory[1] = {0};
    rollDice_theory(dice_num, 0, face_num, freq, total_theory);

    double avg;
    printf("Sum\tFrequency\tTheoretical value\tbias\n");
    for (int i = dice_num; i <= dice_num * face_num; i++){
        avg = (double)freq[i] * d_time / total_theory[0];
        printf("%d\t%d\t\t%.0lf\t\t\t(%5.1lf %)\n", i, result[i], avg, ((result[i]/avg)-1)*100);
    }
    
    free(result);
    free(freq);
    
    return 0;
}