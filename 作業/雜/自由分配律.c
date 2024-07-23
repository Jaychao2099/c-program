# include <stdio.h>
# include <stdlib.h>
# include <math.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int *cal_ratio(double a, double b){
    int gcd_ab;
    int *result = (int *)malloc(2 * sizeof(int));
    a = round(a * 10000);
    b = round(b * 10000);
    gcd_ab = gcd(a,b);
    a = a / gcd_ab;
    b = b / gcd_ab;
    result[0] = pow(a,2) + 2*a*b;
    result[1] = pow(b,2);
    return result;
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
    
    freq = (double *)malloc(num * sizeof(double));
    ratio = (int **)malloc(num * sizeof(int*));
    for (int i = 0; i < num; i++) ratio[i] = (int *)malloc(2 * sizeof(int));  // 分配第二層指標數組
    result = (int *)malloc(pow(2, num) * sizeof(int));
    
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
    for (int i = 0; i < num; i++) free(ratio[i]);
    free(ratio);
    free(result);

    return 0;
}