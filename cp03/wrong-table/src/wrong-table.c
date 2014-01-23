/*
 *      $> gcc wrong-table.c -Wall -pedantic -std=c89 -lm -o wrong-table
 *      $> ./wrong-table 
 *      Input number of evaluations: 10
 *                             Machine epsylone is 0.0000000000000002
 *              Table Taylor's series of values and standard functions for
 *                               f(x)= 1/(4-x*x*x*x)
 *      ---------------------------------------------------------------------
 *      | value of x |      sum of series     |      value of f     | iters |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.00    |   0.25000000000000000  | 0.25000000000000000 |   1   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.10    |   0.25000625015625388  | 0.25000625015625394 |   4   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.20    |   0.25010004001600633  | 0.25010004001600639 |   5   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.30    |   0.25050727723640370  | 0.25050727723640376 |   6   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.40    |   0.25161030595813189  | 0.25161030595813205 |   7   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.50    |   0.25396825396825395  | 0.25396825396825395 |   9   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.60    |   0.25837122778007432  | 0.25837122778007443 |   11   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.70    |   0.26596452033298762  | 0.26596452033298756 |   13   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.80    |   0.27852049910873433  | 0.27852049910873439 |   16   |
 *      |------------|------------------------|---------------------|-------|
 *      |    0.90    |   0.29905200514369434  | 0.29905200514369445 |   20   |
 *      |------------|------------------------|---------------------|-------|
 *      |    1.00    |   0.33333333333333304  | 0.33333333333333326 |   25   |
 *      ---------------------------------------------------------------------
 *                          Maximal error = 0.00000000000000022
 */

#include <stdio.h>
#include <math.h>

#define ITER 100

double findent(double x) {
    return x;
}

double epsylone() {
    double eps = 1.0;

    while (findent(eps / 2 + 1) > 1)
        eps = eps / 2;
    return eps;
}

/* Функция степени */
double power(double x, int n) {
    int i;
    double p = 1;

    for (i = 0; i < n; i++)
        p = p * x;
    return p;
}

/* Вычисление факториала */
double fact(double n) {
    if (n <= 1)
        return 1;
    else
        return fact(n - 1) * n;
}

/* Ряд Тейлора */
double taylor(double n, double x) {
    return power(x, 4 * n) / power(4, n + 1);;
}

int main() {
    double a = 0.0, b = 1.0, x = 0.0, sumT = 0.0;
    int k = 1, n = 0, parts;
    double func, keps, termT, termM, step, max = 0.0;

    /* Ввод количества разбиений отрезка */
    printf("Input number of evaluations: ");
    scanf("\n%d", &parts);
    /* Подсчет количества шагов */
    step = (b - a) / parts;
    keps = k * epsylone();
    printf("                     Machine epsylone is %.16f\n", epsylone());
    printf("        Table Taylor's series of values and standard functions for\n");
    printf("                       f(x)= 1/(4-x*x*x*x)\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" | value of x |      sum of series     |      value of f     | iters |\n");

    /* В условии x <= (keps + b) следует взять некоторую окрестность (keps), 
     * так как в некоторых случаях конец отрезка не считается. 
     * Это происходит из-за погрешности при сложении вещественных чисел.
     */
    for (a = 0.0; x <= (keps + b); x += step) {
        /* Цикл на количество итерации */
        for (n = 0; n < ITER; n++) {
            /* Промежуточное значение ряда Тейлора */
            termT = taylor(n, x);
            /* Условие подсчета суммы Тейлора */
            if (keps >= fabs(termT))
                break;
            /* Сложение членов ряда Тейлора :) */
            sumT = sumT + termT;
        }
        /* Исходная функция */
        func = 1 / (4 - x * x * x * x);
        /* Подсчет погрешности вычислений */
        termM = fabs(func - sumT);
        if (termM >= max)
            max = termM;
        printf(" |------------|------------------------|---------------------|-------|\n");
        printf(" |    %.2f    |   %.17f  | %.17f |   %d   |\n", x, sumT, func, n);
        sumT = 0;
        n = 0;
    }
    printf(" ---------------------------------------------------------------------\n");
    printf("                     Maximal error = %.17f\n", max);
    return 0;
}
