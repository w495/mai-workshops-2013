/**
 * 
 *      $> gcc ./myfloat_t.c -Wall -pedantic -std=c89 -lm -o myfloat_t
 *      $> ./myfloat_t 
 *      10
 *      eps = 0.0000001 
 *      width = 7 
 *      delta = 0.050000 
 *      
 *        # |         x |    target |    taylor |  iter |  target - taylor 
 *      
 *        0 | 0.1000000 | 0.0003327 | 0.0003327 |     2 |  0.0000000
 *        1 | 0.1500000 | 0.0011200 | 0.0011199 |     2 |  0.0000001
 *        2 | 0.2000000 | 0.0026457 | 0.0026457 |     3 | -0.0000000
 *        3 | 0.2500000 | 0.0051449 | 0.0051450 |     3 | -0.0000001
 *        4 | 0.3000000 | 0.0088440 | 0.0088439 |     4 |  0.0000000
 *        5 | 0.3500000 | 0.0139588 | 0.0139587 |     4 |  0.0000001
 *        6 | 0.4000000 | 0.0206937 | 0.0206937 |     5 | -0.0000000
 *        7 | 0.4500000 | 0.0292409 | 0.0292409 |     6 |  0.0000000
 *        8 | 0.5000001 | 0.0397798 | 0.0397796 |     6 |  0.0000001
 *        9 | 0.5500001 | 0.0524766 | 0.0524766 |     8 |  0.0000000
 *       10 | 0.6000001 | 0.0674853 | 0.0674853 |     9 | -0.0000000
 */

#include <stdio.h>
#include <math.h>

typedef double myfloat_t;

const myfloat_t A = 0.1, B = 0.6;
const myfloat_t COEF = 1.0;

const int ITER_MAX = 100;

myfloat_t findent(myfloat_t x) {
    return x;
}

myfloat_t epsilon() {
    myfloat_t e = 1.0;

    while (findent(e / 2 + 1) > 1)
        e = e / 2;
    return e;
}

myfloat_t power(myfloat_t x, int n) {
    int i;
    myfloat_t p = 1;

    for (i = 0; i < n; i++)
        p = p * x;
    return p;
}

myfloat_t absolute(myfloat_t x) {
    if (x < 0)
        return -x;
    return x;
}

myfloat_t target_function(myfloat_t x) {
    return (1 + x * x) / 2 * atan(x) - x / 2;
}

myfloat_t taylor_function(myfloat_t x, int n) {
    return pow(-1, n + 1) * pow(x, 2 * n + 1) / (4 * n * n - 1);
}

int main() {
    int step = 0;
    int steps = 0;
    myfloat_t delta;
    myfloat_t eps = epsilon();
    myfloat_t x = A;
    int width = ceil(-log10(eps));
    int swidth = width + 2;

    scanf("%d", &steps);
    delta = (B - A) / steps;
    printf("eps = %.*f \n", width, eps);
    printf("width = %d \n", width);
    printf("delta = %f \n", delta);
    printf("\n");
    printf(
        "%3s | %*s | %*s | %*s | %5s |  %*s \n\n",
        "#",
        swidth, "x",
        swidth, "target",
        swidth, "taylor", "iter", 
        swidth, "target - taylor"
    );
    for (step = 0; step != (steps + 1); ++step) {
        myfloat_t target = target_function(x);
        int iter = 1;
        myfloat_t taylor = taylor_function(x, iter);

        while ((absolute(taylor - target) >= eps * COEF)
               && (iter < ITER_MAX)) {
            iter = iter + 1;
            taylor += taylor_function(x, iter);
        }
        printf(
            "%3d | %.*f | %.*f | %.*f | %5d | %*.*f\n",
            step,
            width,
            x,
            width, target,
            width, taylor, 
            iter, 
            width + 3, width, target - taylor
        );
        x = x + delta;
    }
    printf("\n");
    return 0;
}
