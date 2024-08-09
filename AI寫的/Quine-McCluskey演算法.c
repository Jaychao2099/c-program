#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_VARS 20
#define MAX_TERMS 1000

typedef struct {
    int minterm;
    char binary[MAX_VARS + 1];
    int used;
} Term;

int numVars;
int numTerms;
Term terms[MAX_TERMS];
Term primeImplicants[MAX_TERMS];
int numPrimeImplicants = 0;

void decimalToBinary(int decimal, char* binary, int numVars) {
    for (int i = numVars - 1; i >= 0; i--) {
        binary[i] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binary[numVars] = '\0';
}

int countOnes(char* binary) {
    int count = 0;
    for (int i = 0; binary[i]; i++) {
        if (binary[i] == '1') count++;
    }
    return count;
}

int canCombine(char* binary1, char* binary2) {
    int diff = 0;
    for (int i = 0; binary1[i]; i++) {
        if (binary1[i] != binary2[i]) diff++;
    }
    return (diff == 1);
}

void combine(char* binary1, char* binary2, char* result) {
    for (int i = 0; binary1[i]; i++) {
        if (binary1[i] != binary2[i])
            result[i] = '-';
        else
            result[i] = binary1[i];
    }
    result[numVars] = '\0';
}

void findPrimeImplicants() {
    Term newTerms[MAX_TERMS];
    int numNewTerms;

    do {
        numNewTerms = 0;
        for (int i = 0; i < numTerms; i++) {
            for (int j = i + 1; j < numTerms; j++) {
                if (canCombine(terms[i].binary, terms[j].binary)) {
                    terms[i].used = terms[j].used = 1;
                    Term newTerm;
                    combine(terms[i].binary, terms[j].binary, newTerm.binary);
                    newTerm.minterm = -1;  // Combined term doesn't have a single minterm
                    newTerm.used = 0;
                    newTerms[numNewTerms++] = newTerm;
                }
            }
        }

        for (int i = 0; i < numTerms; i++) {
            if (!terms[i].used) {
                primeImplicants[numPrimeImplicants++] = terms[i];
            }
        }

        memcpy(terms, newTerms, numNewTerms * sizeof(Term));
        numTerms = numNewTerms;
    } while (numNewTerms > 0);
}

void printPrimeImplicants() {
    printf("Prime Implicants:\n");
    for (int i = 0; i < numPrimeImplicants; i++) {
        printf("%s\n", primeImplicants[i].binary);
    }
}

int main() {
    printf("Enter the number of variables: ");
    scanf("%d", &numVars);

    printf("Enter the number of minterms: ");
    scanf("%d", &numTerms);

    printf("Enter the minterms:\n");
    for (int i = 0; i < numTerms; i++) {
        scanf("%d", &terms[i].minterm);
        decimalToBinary(terms[i].minterm, terms[i].binary, numVars);
        terms[i].used = 0;
    }

    findPrimeImplicants();
    printPrimeImplicants();

    return 0;
}