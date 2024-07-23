# include <stdio.h>
# include <stdlib.h>
# include <math.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int cal_ratio(double a, double b){
    int gcd_ab, result[2];
    a = round(a * 10000);
    b = round(b * 10000);
    gcd_ab = gcd(a,b);
    result[0] = a / gcd_ab;
    result[1] = b / gcd_ab;
    return &result[0];
}

int main(){
    int num;
    double *freq;
    int **ratio, *result;

    printf("Number of allele (1~26): ");
    if (scanf("%d", &num) != 1 || num < 1 || num > 26){
        printf("Plz enter 1 ~ 26");
        return 1;
    }
    
    freq = malloc(num * sizeof(double));
    ratio = malloc(num * 3 * sizeof(int));
    result = malloc(pow(2, num) * sizeof(int));
    
    for (int i = 0; i < num; i++){
        printf("allel-%d dominant gene frequency (0~1): ", i+1);
        if (scanf("%lf", &freq[i]) != 1 || freq[i] < 0 || freq[i] > 1){
            printf("Plz enter 0 ~ 1");
            return 1;
        }
        ratio[i] = cal_ratio(freq[i], 1 - freq[i]);
    }

    for (int i = 0; i < pow(2, num); i++){
        result[i] = 1;
        int temp = i/pow(2,num-i-1);
        for (int j = 0; j < num; j++){
            result[i] = result[i] * ratio[j][temp];
        }
    }

    for (int i = 0; i < pow(2, num); i++){
        printf("%d", result[i]);
        if (i < pow(2, num)) printf(":");
    }

    free(freq);
    free(ratio);
    free(result);

    return 0;
}