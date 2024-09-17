# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main(){
    int num;
    unsigned long long time1 = time(0);

    printf("How many random numbers? ");
    scanf("%d", &num);
    int *num_add = &num;

    unsigned long long time2 = time(0);

    unsigned long long temp = (long long)num_add % (time1 - time2);
    srand(temp);
    temp = rand();
    srand(temp);

    printf("temp = %llu\n\n", temp);

    for (int i = 0; i < num; i++){
        printf("%d\n", rand());
    }
    return 0;
}