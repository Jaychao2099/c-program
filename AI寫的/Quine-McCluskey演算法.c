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
    int essential;
} Term;

int numVars;
int numTerms;
int numDontCares;
Term terms[MAX_TERMS];
Term primeImplicants[MAX_TERMS];
int numPrimeImplicants = 0;
int* minterms;
int* dontCares;

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
                    newTerm.minterm = -1;
                    newTerm.used = 0;
                    newTerm.essential = 0;
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

int covers(char* implicant, int minterm) {
    char mintermBinary[MAX_VARS + 1];
    decimalToBinary(minterm, mintermBinary, numVars);
    for (int i = 0; i < numVars; i++) {
        if (implicant[i] != '-' && implicant[i] != mintermBinary[i]) {
            return 0;
        }
    }
    return 1;
}

void findEssentialPrimeImplicants() {
    int* covered = (int*)calloc(numTerms, sizeof(int));
    
    for (int i = 0; i < numPrimeImplicants; i++) {
        int coverCount = 0;
        int lastCovered = -1;
        for (int j = 0; j < numTerms; j++) {
            if (covers(primeImplicants[i].binary, minterms[j])) {
                coverCount++;
                lastCovered = j;
            }
        }
        if (coverCount == 1 && !covered[lastCovered]) {
            primeImplicants[i].essential = 1;
            covered[lastCovered] = 1;
        }
    }
    
    free(covered);
}

void printMinimalCover() {
    printf("Minimal Cover:\n");
    for (int i = 0; i < numPrimeImplicants; i++) {
        if (primeImplicants[i].essential) {
            printf("%s (Essential)\n", primeImplicants[i].binary);
        }
    }
    // Here you might want to add logic for including non-essential prime implicants
    // to cover any remaining uncovered minterms
}

int evaluateFunction(char* input) {
    for (int i = 0; i < numPrimeImplicants; i++) {
        if (primeImplicants[i].essential) {
            int match = 1;
            for (int j = 0; j < numVars; j++) {
                if (primeImplicants[i].binary[j] != '-' && primeImplicants[i].binary[j] != input[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) return 1;
        }
    }
    return 0;
}

int main() {
    printf("Enter the number of variables: ");
    scanf("%d", &numVars);

    printf("Enter the number of minterms: ");
    scanf("%d", &numTerms);

    minterms = (int*)malloc(numTerms * sizeof(int));
    printf("Enter the minterms:\n");
    for (int i = 0; i < numTerms; i++) {
        scanf("%d", &minterms[i]);
        terms[i].minterm = minterms[i];
        decimalToBinary(minterms[i], terms[i].binary, numVars);
        terms[i].used = 0;
        terms[i].essential = 0;
    }

    printf("Enter the number of don't cares: ");
    scanf("%d", &numDontCares);

    dontCares = (int*)malloc(numDontCares * sizeof(int));
    printf("Enter the don't cares:\n");
    for (int i = 0; i < numDontCares; i++) {
        scanf("%d", &dontCares[i]);
        terms[numTerms + i].minterm = dontCares[i];
        decimalToBinary(dontCares[i], terms[numTerms + i].binary, numVars);
        terms[numTerms + i].used = 0;
        terms[numTerms + i].essential = 0;
    }

    numTerms += numDontCares;

    findPrimeImplicants();
    findEssentialPrimeImplicants();
    printMinimalCover();

    char input[MAX_VARS + 1];
    while (1) {
        printf("\nEnter a binary input to evaluate (or 'q' to quit): ");
        scanf("%s", input);
        if (input[0] == 'q') break;
        if (strlen(input) != numVars) {
            printf("Invalid input length. Please enter %d bits.\n", numVars);
            continue;
        }
        int result = evaluateFunction(input);
        printf("Function output: %d\n", result);
    }

    free(minterms);
    free(dontCares);
    return 0;
}