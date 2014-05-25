/**
 * @file    libformat.с
 *          Файл реализации функций работы с таблицей
 * 
 * @package libformat
 *          Вывод табличных данных.
 */ 

/*
 * Подключаем только один заголовочный файл. 
 * В нем иже сделаны все нужные определения и включения.
 */ 
#include "libformat.h"

/**
 * @fn  Выводит на экран линию для таблицы значений.
 *      Чтобы понять, что происходит, читайте документацию к printf.
 */
void format_print_table_line(int stepwidth, int iterwidth, int epswidth) {
    int epslength = epswidth + FORMAT_REAL_LENGTH;
    int size = stepwidth + 3 * epslength + iterwidth + FORMAT_LINE_OFFSET;
    int i;

    for (i = 0; i != size; ++i) {
        printf("-");
    }
    printf("\n");
}

/**
 * @fn  Выводит на экран заголовок для таблицы значений.
 *      Чтобы понять, что происходит, читайте документацию к printf.
 */
void format_print_table_head(int stepwidth, int iterwidth, int epswidth) {
    int epslength = epswidth + FORMAT_REAL_LENGTH;

    printf("|%*s |", stepwidth, "#");
    printf(" %*s |", epslength, "x");
    printf(" %*s |", epslength, "target");
    printf(" %*s |", epslength, "taylor");
    printf(" %*s |\n", iterwidth, "n");
}

/**
 * @fn  Выводит на экран строку для таблицы значений.
 *      Чтобы понять, что происходит, читайте документацию к printf.
 */
void format_print_table_row(
    int stepwidth,
    int iterwidth,
    int epswidth,
    step_t step,
    real_t x,
    real_t target, 
    real_t taylor, 
    iter_t iter
) {
    int epslength = epswidth + FORMAT_REAL_LENGTH;

    printf("|%*" FORMAT_STEP " |", stepwidth, step);
    printf(" %*.*" FORMAT_REAL " |", epslength, epswidth, x);
    printf(" %*.*" FORMAT_REAL " |", epslength, epswidth, target);
    printf(" %*.*" FORMAT_REAL " |", epslength, epswidth, taylor);
    printf(" %*" FORMAT_ITER " |\n", iterwidth, iter);
}
