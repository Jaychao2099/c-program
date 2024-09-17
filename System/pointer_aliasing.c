# include <stdio.h>
# include <stdlib.h>

void copy(int *a, int *b){
    *a++ = *b++;
    *a++ = *b++;
}

int main(){
    int p = 69;
    int *test_a, *test_b = calloc(3, sizeof(int));

    test_a = test_b;
    *test_b = p;

    printf("p = %d\n", p);
    printf("a = %x, b = %x\n", test_a, test_b);
    printf("a[0] = %d, b[0] = %d\n", test_a[0], test_b[0]);
    printf("a[1] = %d, b[1] = %d\n", test_a[1], test_b[1]);
    printf("a[2] = %d, b[2] = %d\n", test_a[2], test_b[2]);
    
    copy(test_a, test_b);

    printf("------------\n");

    printf("p = %d\n", p);
    printf("a = %x, b = %x\n", test_a, test_b);
    printf("a[0] = %d, b[0] = %d\n", test_a[0], test_b[0]);
    printf("a[1] = %d, b[1] = %d\n", test_a[1], test_b[1]);
    printf("a[2] = %d, b[2] = %d\n", test_a[2], test_b[2]);

    free(test_a);
    free(test_b);

    return 0;
}