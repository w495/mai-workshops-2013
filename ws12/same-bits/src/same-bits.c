#include<stdio.h>

int main() {
    int a, b, i, c = -1;

    scanf("%d%d", &a, &b);

    for (i = a; i > 0; i /= 10) {
        if (c == i % 10)
            break;
        else
            c = i % 10;
    }

    if (i > 0)
        printf("false ");
    else
        printf("true ");

    for (i = b; i > 0; i /= 10) {
        if (c == i % 10)
            break;
        else
            c = i % 10;
    }

    if (i > 0)
        printf("false ");
    else
        printf("true ");

    printf("\n");
    return 0;
}
