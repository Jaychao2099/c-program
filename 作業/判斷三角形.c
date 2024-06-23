# include <stdio.h>

int main(){
    int side_1, side_2, side_3;
    printf("Please enter the lengths of the triangle:");
    scanf("%d%d%d", &side_1, &side_2, &side_3);
    if((side_1 == side_2) * (side_2 == side_3)){
        printf("Regular triangle\n");
    }
    else {
            printf("Not a Regular triangle");
        }
    return 0;
}