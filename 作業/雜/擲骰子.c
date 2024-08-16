# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main(){
    int num;
    unsigned long long time1 = time(0);

    printf("How many dice? ");
    scanf("%d", &num);

    /*
    int *num_add = &num;

    unsigned long long time2 = time(0);

    unsigned long long temp = (long long)num_add % (time1 - time2);
    srand(temp);
    temp = rand();
    srand(temp);
    */
    srand(time1);

    int loop;
    int one=0, two=0, three=0, four=0, five=0, six=0;

    for (int i = 0; i < num; i++){
        loop = rand() % 6 + 1;
        //printf("%d\n", loop);
        switch (loop){
        case 1:
            one++;
            break;
        case 2:
            two++;
            break;
        case 3:
            three++;
            break;
        case 4:
            four++;
            break;
        case 5:
            five++;
            break;
        case 6:
            six++;
            break;
        }
    }
    printf("one   = %d\ntwo   = %d\nthree = %d\nfour  = %d\nfive  = %d\nsix   = %d\n", one, two, three, four, five, six);
    return 0;
}