# include <stdio.h>
# include <math.h>

# define max(a, b) ((a) > (b) ? (a) : (b))
# define min(a, b) ((a) < (b) ? (a) : (b))

int main(){
    double a, b, c;
    printf("Please enter the lengths of the triangle: ");
    if (scanf("%lf%lf%lf", &a, &b, &c) != 3 || a <= 0 || b <= 0 || c <= 0) {
        printf("Invalid input. Please enter positive numbers.\n");
        return 1;
    }

    double side_max = max(max(a, b), c);
    double side_min = min(min(a, b), c);
    double side_mid = a + b + c - side_max - side_min;

    int case_Rectangular = fabs(side_max*side_max - side_mid*side_mid - side_min*side_min) < 1e-10;
    int case_Isosceles = (a == b || b == c || c == a);

    printf("This is ");
    if (a + b + c - side_max <= side_max) {
        printf("NOT a triangle!\n");
    }
    else if (a == b && b == c){
        printf("a Regular triangle\n");
    }
    else if (case_Rectangular && case_Isosceles) {
        printf("a Rectangular Isosceles triangle\n");
    }
    else if (case_Rectangular){
        printf("a Rectangular triangle\n");
    }
    else if (case_Isosceles){
        printf("a Isosceles triangle\n");
    }
    else {
        printf("just a normal triangle, nothing special.\n");
    }
    return 0;
}