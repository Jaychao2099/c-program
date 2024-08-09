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
    int diff = 0, diffPos = -1;
    for (int i = 0; i < vars; i++) {
        if (t1->bits[i] != t2->bits[i]) {
            diff++;
            diffPos = i;
        }
    }
    return (diff == 1) ? diffPos : -1;
}

void combine(Term *t1, Term *t2, Term *result, int vars) {
    for (int i = 0; i < vars; i++) {
        if (t1->bits[i] != t2->bits[i]) result->bits[i] = 2;
        else result->bits[i] = t1->bits[i];
    }
    result->used = 0;
    result->combined = 0;
}

int termExists(TermArray *array, Term *term, int vars) {
    for (int i = 0; i < array->count; i++) {
        if (memcmp(array->terms[i].bits, term->bits, vars * sizeof(int)) == 0) {
            return 1;
        }
    }
    return 0;
}

void simplify(TermArray *input, TermArray *output, int vars) {
    for (int i = 0; i < input->count; i++) {
        for (int j = i + 1; j < input->count; j++) {
            int diffPos = compareBits(&input->terms[i], &input->terms[j], vars);
            if (diffPos != -1) {
                Term newTerm;
                combine(&input->terms[i], &input->terms[j], &newTerm, vars);
                input->terms[i].combined = 1;
                input->terms[j].combined = 1;
                if (!termExists(output, &newTerm, vars)) {
                    output->terms[output->count++] = newTerm;
                }
            }
        }
    }
    
    for (int i = 0; i < input->count; i++) {
        if (!input->terms[i].combined && !termExists(output, &input->terms[i], vars)) {
            output->terms[output->count++] = input->terms[i];
        }
    }
}

void generatePrimeImplicants(TermArray *minterms, TermArray *dontCares, TermArray *primeImplicants, int vars) {
    TermArray current = { .count = 0 };
    TermArray next;
    
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
    int essentialCount = 0;
    for (int i = 0; i < minterms->count; i++) {
        if (!minterms->terms[i].used) {
            int match = 1;
            for (int j = 0; j < vars; j++) {
                if (primeImplicant->bits[j] != 2 && primeImplicant->bits[j] != minterms->terms[i].bits[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) essentialCount++;
        }
    }
    return (essentialCount == 1);
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
    
    if (minimalCover->count == 0) {
        printf("0");  // If minimal cover is empty, function is always 0
        return;
    }
    
    for (int i = 0; i < minimalCover->count; i++) {
        int termPrinted = 0;
        for (int j = 0; j < vars; j++) {
            if (minimalCover->terms[i].bits[j] == 0) {
                printf("%c'", 'A' + j);
                termPrinted = 1;
            } else if (minimalCover->terms[i].bits[j] == 1) {
                printf("%c", 'A' + j);
                termPrinted = 1;
            }
        }
        if (!termPrinted) {
            printf("1");  // If term is all don't cares, it's always true
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
    TermArray minterms = { .count = 0 };
    TermArray dontCares = { .count = 0 };
    TermArray primeImplicants = { .count = 0 };
    TermArray essentialPIs = { .count = 0 };
    TermArray minimalCover = { .count = 0 };
    
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
    
    printf("Enter number of don't cares: ");
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
    
    findEssentialPrimeImplicants(&primeImplicants, &minterms, &essentialPIs, vars);
    
    printf("\nEssential Prime Implicants:\n");
    for (int i = 0; i < essentialPIs.count; i++) {
        printTerm(&essentialPIs.terms[i], vars);
        printf("\n");
    }
    
    minimalCover = essentialPIs;  // For now, the minimal cover is just the essential PIs
    
    printf("\nSimplified Boolean Function:\n");
    generateBooleanFunction(&minimalCover, vars);
    
    int input[MAX_VARS];
    printf("\nEnter inputs to evaluate (space-separated, 1 and 0 only):\n");
    for (int i = 0; i < vars; i++) {
        scanf("%d", &input[i]);
    }
    
    int result = evaluateFunction(&minimalCover, input, vars);
    printf("Function evaluates to: %d\n", result);
    
    return 0;
}
