#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_TRAITS 26
#define MAX_PHENOTYPES 67108864  // 3^26, 最大可能的表型數量

// 結構體定義
typedef struct {
    char phenotype[MAX_TRAITS + 1];
    double frequency;
} PhenotypeFreq;

// 函數聲明
int validate_trait_count(int num_traits);
int validate_allele_frequency(double freq);
void calculate_trait_ratios(int num_traits, double* dominant_allele_freqs, PhenotypeFreq* phenotype_freqs, int* phenotype_count);
void simplify_ratios(double* ratios, int count, int* simplified);
int gcd(int a, int b);
int lcm(int a, int b);

int validate_trait_count(int num_traits) {
    if (num_traits < 1 || num_traits > 26) {
        printf("錯誤: 性狀數量必須在1到26之間。\n");
        return 1;
    }
    return 0;
}

int validate_allele_frequency(double freq) {
    if (freq < 0 || freq > 1) {
        printf("錯誤: 等位基因頻率必須在0到1之間。\n");
        return 1;
    }
    return 0;
}

void calculate_trait_ratios(int num_traits, double* dominant_allele_freqs, PhenotypeFreq* phenotype_freqs, int* phenotype_count) {
    int total_combinations = 1 << num_traits;
    *phenotype_count = 0;

    for (int i = 0; i < total_combinations; i++) {
        double freq = 1.0;
        char phenotype[MAX_TRAITS + 1] = {0};

        for (int j = 0; j < num_traits; j++) {
            if (i & (1 << j)) {
                phenotype[j] = 'A' + j;
                freq *= dominant_allele_freqs[j];
            } else {
                phenotype[j] = 'a' + j;
                freq *= (1 - dominant_allele_freqs[j]);
            }
        }

        // 檢查是否已存在相同的表型
        int found = 0;
        for (int k = 0; k < *phenotype_count; k++) {
            if (strcmp(phenotype_freqs[k].phenotype, phenotype) == 0) {
                phenotype_freqs[k].frequency += freq;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(phenotype_freqs[*phenotype_count].phenotype, phenotype);
            phenotype_freqs[*phenotype_count].frequency = freq;
            (*phenotype_count)++;
        }
    }
}

void simplify_ratios(double* ratios, int count, int* simplified) {
    double min_ratio = ratios[0];
    for (int i = 1; i < count; i++) {
        if (ratios[i] < min_ratio) min_ratio = ratios[i];
    }

    int lcm_denominator = 1;
    for (int i = 0; i < count; i++) {
        double scaled = ratios[i] / min_ratio;
        int denominator = 1;
        while (fabs(scaled * denominator - round(scaled * denominator)) > 1e-6) {
            denominator *= 10;
        }
        lcm_denominator = lcm(lcm_denominator, denominator);
    }

    for (int i = 0; i < count; i++) {
        simplified[i] = round(ratios[i] / min_ratio * lcm_denominator);
    }

    // 找最大公約數並簡化
    int gcd_all = simplified[0];
    for (int i = 1; i < count; i++) {
        gcd_all = gcd(gcd_all, simplified[i]);
    }
    for (int i = 0; i < count; i++) {
        simplified[i] /= gcd_all;
    }
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int num_traits;
    double dominant_allele_freqs[MAX_TRAITS];
    PhenotypeFreq phenotype_freqs[MAX_PHENOTYPES];
    int phenotype_count = 0;

    // 獲取並驗證性狀數量
    printf("請輸入性狀的數量(1-26之間): ");
    if (scanf("%d", &num_traits) != 1) {
        printf("錯誤: 輸入無效。\n");
        return 1;
    }
    
    if (validate_trait_count(num_traits) != 0) {
        return 1;
    }

    // 獲取並驗證每個性狀的顯性等位基因頻率
    for (int i = 0; i < num_traits; i++) {
        while (1) {
            printf("請輸入第 %d 個性狀的顯性等位基因頻率 (0-1 之間): ", i + 1);
            if (scanf("%lf", &dominant_allele_freqs[i]) != 1) {
                printf("錯誤: 輸入無效。請重新輸入。\n");
                while (getchar() != '\n');  // 清空輸入緩衝區
                continue;
            }
            
            if (validate_allele_frequency(dominant_allele_freqs[i]) == 0) {
                break;
            }
        }
    }

    // 計算性狀比例
    calculate_trait_ratios(num_traits, dominant_allele_freqs, phenotype_freqs, &phenotype_count);

    // 打印結果
    printf("\n各種表型組合的頻率: \n");
    for (int i = 0; i < phenotype_count; i++) {
        printf("%s: %.4f\n", phenotype_freqs[i].phenotype, phenotype_freqs[i].frequency);
    }

    // 轉換為最簡整數比
    double ratios[MAX_PHENOTYPES];
    int simplified_ratios[MAX_PHENOTYPES];
    for (int i = 0; i < phenotype_count; i++) {
        ratios[i] = phenotype_freqs[i].frequency;
    }
    simplify_ratios(ratios, phenotype_count, simplified_ratios);

    printf("\n表型比例(最簡整數比): \n");
    printf("比例: ");
    for (int i = 0; i < phenotype_count; i++) {
        printf("%d", simplified_ratios[i]);
        if (i < phenotype_count - 1) printf(" : ");
    }
    printf("\n表型: ");
    for (int i = 0; i < phenotype_count; i++) {
        printf("%s", phenotype_freqs[i].phenotype);
        if (i < phenotype_count - 1) printf(" : ");
    }
    printf("\n");

    return 0;
}