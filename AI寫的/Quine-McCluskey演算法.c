#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_VARS 10
#define MAX_TERMS 1024

typedef struct {
    int bits[MAX_VARS];
    int used;
    int combined;
} Term;

typedef struct {
    Term terms[MAX_TERMS];
    int count;
} TermArray;

void printTerm(Term *term, int vars) {
    for (int i = 0; i < vars; i++) {
        if (term->bits[i] == 2) printf("-");
        else printf("%d", term->bits[i]);
    }
}

int compareBits(Term *t1, Term *t2, int vars) {
    int diff = 0;
    for (int i = 0; i < vars; i++) {
        if (t1->bits[i] != t2->bits[i]) diff++;
    }
    return diff;
}

void combine(Term *t1, Term *t2, Term *result, int vars) {
    for (int i = 0; i < vars; i++) {
        if (t1->bits[i] != t2->bits[i]) result->bits[i] = 2;
        else result->bits[i] = t1->bits[i];
    }
}

void simplify(TermArray *input, TermArray *output, int vars) {
    for (int i = 0; i < input->count; i++) {
        for (int j = i + 1; j < input->count; j++) {
            if (compareBits(&input->terms[i], &input->terms[j], vars) == 1) {
                Term newTerm;
                combine(&input->terms[i], &input->terms[j], &newTerm, vars);
                input->terms[i].combined = 1;
                input->terms[j].combined = 1;
                newTerm.used = 0;
                newTerm.combined = 0;
                output->terms[output->count++] = newTerm;
            }
        }
    }
    
    for (int i = 0; i < input->count; i++) {
        if (!input->terms[i].combined) {
            output->terms[output->count++] = input->terms[i];
        }
    }
}

void generatePrimeImplicants(TermArray *minterms, TermArray *dontCares, TermArray *primeImplicants, int vars) {
    TermArray current, next;
    current.count = 0;
    
    for (int i = 0; i < minterms->count; i++) {
        current.terms[current.count++] = minterms->terms[i];
    }
    for (int i = 0; i < dontCares->count; i++) {
        current.terms[current.count++] = dontCares->terms[i];
    }
    
    while (1) {
        next.count = 0;
        simplify(&current, &next, vars);
        if (next.count == 0) break;
        current = next;
    }
    
    *primeImplicants = current;
}

int isEssentialPrimeImplicant(Term *primeImplicant, TermArray *minterms, int vars) {
    for (int i = 0; i < minterms->count; i++) {
        if (!minterms->terms[i].used) {
            int match = 1;
            for (int j = 0; j < vars; j++) {
                if (primeImplicant->bits[j] != 2 && primeImplicant->bits[j] != minterms->terms[i].bits[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                int count = 0;
                for (int k = 0; k < minterms->count; k++) {
                    if (!minterms->terms[k].used) {
                        int subMatch = 1;
                        for (int l = 0; l < vars; l++) {
                            if (primeImplicant->bits[l] != 2 && primeImplicant->bits[l] != minterms->terms[k].bits[l]) {
                                subMatch = 0;
                                break;
                            }
                        }
                        if (subMatch) count++;
                    }
                }
                if (count == 1) return 1;
            }
        }
    }
    return 0;
}

void findEssentialPrimeImplicants(TermArray *primeImplicants, TermArray *minterms, TermArray *essentialPIs, int vars) {
    for (int i = 0; i < primeImplicants->count; i++) {
        if (isEssentialPrimeImplicant(&primeImplicants->terms[i], minterms, vars)) {
            essentialPIs->terms[essentialPIs->count++] = primeImplicants->terms[i];
            for (int j = 0; j < minterms->count; j++) {
                int match = 1;
                for (int k = 0; k < vars; k++) {
                    if (primeImplicants->terms[i].bits[k] != 2 && primeImplicants->terms[i].bits[k] != minterms->terms[j].bits[k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) minterms->terms[j].used = 1;
            }
        }
    }
}

void generateBooleanFunction(TermArray *minimalCover, int vars) {
    printf("f(");
    for (int i = 0; i < vars; i++) {
        printf("%c", 'A' + i);
        if (i < vars - 1) printf(",");
    }
    printf(") = ");
    
    for (int i = 0; i < minimalCover->count; i++) {
        for (int j = 0; j < vars; j++) {
            if (minimalCover->terms[i].bits[j] == 0) {
                printf("%c'", 'A' + j);
            } else if (minimalCover->terms[i].bits[j] == 1) {
                printf("%c", 'A' + j);
            }
        }
        if (i < minimalCover->count - 1) printf(" + ");
    }
    printf("\n");
}

int evaluateFunction(TermArray *minimalCover, int *input, int vars) {
    for (int i = 0; i < minimalCover->count; i++) {
        int match = 1;
        for (int j = 0; j < vars; j++) {
            if (minimalCover->terms[i].bits[j] != 2 && minimalCover->terms[i].bits[j] != input[j]) {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}

int main() {
    int vars, mintermCount, dontCareCount;
    TermArray minterms, dontCares, primeImplicants, essentialPIs, minimalCover;
    
    printf("Enter number of variables: ");
    scanf("%d", &vars);
    
    printf("Enter number of minterms: ");
    scanf("%d", &mintermCount);
    
    printf("Enter minterms in binary (space-separated):\n");
    for (int i = 0; i < mintermCount; i++) {
        for (int j = 0; j < vars; j++) {
            scanf("%1d", &minterms.terms[i].bits[j]);
        }
        minterms.terms[i].used = 0;
        minterms.terms[i].combined = 0;
    }
    minterms.count = mintermCount;
    
    printf("Enter number of don't cares:");
    scanf("%d", &dontCareCount);
    
    if (dontCareCount > 0) {
        printf("Enter don't cares in binary (space-separated):\n");
        for (int i = 0; i < dontCareCount; i++) {
            for (int j = 0; j < vars; j++) {
                scanf("%1d", &dontCares.terms[i].bits[j]);
            }
            dontCares.terms[i].used = 0;
            dontCares.terms[i].combined = 0;
        }
    }
    dontCares.count = dontCareCount;
    
    generatePrimeImplicants(&minterms, &dontCares, &primeImplicants, vars);
    
    printf("\nPrime Implicants:\n");
    for (int i = 0; i < primeImplicants.count; i++) {
        printTerm(&primeImplicants.terms[i], vars);
        printf("\n");
    }
    
    essentialPIs.count = 0;
    findEssentialPrimeImplicants(&primeImplicants, &minterms, &essentialPIs, vars);
    
    minimalCover = essentialPIs;
    
    printf("\nMinimal Cover:\n");
    for (int i = 0; i < minimalCover.count; i++) {
        printTerm(&minimalCover.terms[i], vars);
        printf("\n");
    }
    
    printf("\nBoolean Function:\n");
    generateBooleanFunction(&minimalCover, vars);
    
    printf("\nEnter a binary input to evaluate (space-separated):\n");
    int input[MAX_VARS];
    for (int i = 0; i < vars; i++) {
        scanf("%d", &input[i]);
    }
    
    int result = evaluateFunction(&minimalCover, input, vars);
    printf("Function output: %d\n", result);
    
    return 0;
}