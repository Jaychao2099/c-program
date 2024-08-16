# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main(){
    int num;

    printf("How many dice? ");
    scanf("%d", &num);

    srand(time(0));

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