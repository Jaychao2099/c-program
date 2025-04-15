#include <stdio.h>
#include <math.h>

#define cbrt(X) _Generic((X), \
    long double: cbrtl,       \
    default: cbrt,            \
    const float: cbrtf,       \
    float: cbrtf)(X)

int main()
{
    double x = 8.0;
    const float y = 7.414;
    printf("cbrt(8.0) = %f\n", cbrt(x));
    printf("cbrtf(7.414) = %f\n", cbrt(y));
}
