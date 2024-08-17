# include <stdio.h>

int upway(int stairs){
    int result;
    if (stairs == 1) return 1;
    if (stairs == 2) return 2;
    else return upway(stairs - 1) + upway(stairs - 2);
}

int main(){
    int num, way;

    printf("Number of stairs: ");
    if (scanf("%d", &num) != 1 || num < 1){
        printf("Input error, must >= 1");
        return 1;
    }

    way = upway(num);
    printf("The number of ways to reach the %d stair: %d\n", num, way);
    return 0;
}