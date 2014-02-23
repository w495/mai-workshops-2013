#include <stdio.h>
#include <math.h>

main() {
    float a, b, c;

    scanf("%f %f %f", &a, &b, &c);

    float d, x1, x2;

    d = b * b - 4 * a * c;

    if (d == 0) {
        float x = (-b) / 2 * a;
        printf("Otvet: x=%f\n", x);
    }
    else if (d < 0) {
        printf("Error\n");
    }
    else if (d > 0) {
        float x1 = ((-b) - sqrt(d)) / 2 * a;
        float x2 = ((-b) + sqrt(d)) / 2 * a;
        printf("\tx1 = %f\tx2 = %f\n", x1, x2);
    }
}
