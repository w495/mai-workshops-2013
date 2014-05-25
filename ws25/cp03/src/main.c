/**
 * @file    main.с
 *          Бизнес-логика проекта. Реализация основных действий программы по заданию.
 * 
 * @package main
 *          Основная логика программы.
 */ 

/*
 * Подключаем только один заголовочный файл. 
 * В нем иже сделаны все нужные определения и включения.
 */ 
#include "main.h"

int main() {

    /**
     * @var Машинное эпсилон.
     */
    real_t eps = epsylone();

    /**
     * @var Точка в которой мы будем вычислять значения функции на каждом шаге.
     */
    real_t x;

    /**
     * @var Смещение точки на каждом шаге. Δx.
     */
    real_t delta_x;

    /**
     * @var Количество интервалов, на которые мы делим отрезок.
     */
    step_t nsteps;

    /**
     * @var Номер шага по оси `x`.
     */
    step_t step;

    /**  
     * @var Ширина машинного эпсилон, 
     *      т.е. сколько десятичных знаков после запятой занимает эпсилон
     *      при печати. Переменная нужна только для красивого вывода на экран.
     */
    int epswidth;

    /**  
     * @var Ширина номера шага, 
     *      т.е. сколько десятичных цифр занимает номер шага при печати. 
     *      Переменная нужна только для красивого вывода на экран.
     */
    int stepwidth;

    /**  
     * @var Ширина номера итерации по Тейлору, 
     *      т.е. сколько десятичных цифр занимает номер итерации при печати. 
     *      Переменная нужна только для красивого вывода на экран.
     */
    int iterwidth;

    /*
     * Считываем количество шагов.
     */
    scanf("%" FORMAT_STEP, &nsteps);

    /*
     * Вычисляем дельту, смещение точки на каждом шаге.
     */
    delta_x = (STOP_X - START_X) / nsteps;

    /*
     * Вычисляем ширину эпсилон.
     */
    epswidth = epslen(eps);

    /*
     * Вычисляем ширину номера шага.
     */
    stepwidth = steplen(nsteps);

    /*
     * Вычисляем ширину номера итерации по тейлору.
     */
    iterwidth = iterlen(ITER_LIMIT);

    /*
     * Рисуем шапку таблицы
     */
    format_print_table_line(stepwidth, iterwidth, epswidth);
    format_print_table_head(stepwidth, iterwidth, epswidth);
    format_print_table_line(stepwidth, iterwidth, epswidth);

    x = START_X;
    for (step = 0; step != (nsteps + 1); ++step) {
        iter_t iter = 0;

        /* Значение нулевого члена ряда Тейлора в точке `x`. */
        real_t taylor = taylor_fuction(x, iter);

        /* Значение целевой функции в точке `x`. */
        real_t target = target_fuction(x);

        while ((rabs(target - taylor) >= (eps * COEF)) && iter < ITER_LIMIT) {
            ++iter;
            /* Значение n-го члена ряда Тейлора в точке `x`. */
            taylor += taylor_fuction(x, iter);
        }

        /*
         * Рисуем строку таблицы.
         */
        format_print_table_row(stepwidth, iterwidth, epswidth,
                               step, x, target, taylor, iter);

        /*
         * Увеличиваем `x` на `Δx`.
         */
        x += delta_x;
    }

    /*
     * Рисуем подол таблицы.
     */
    format_print_table_line(stepwidth, iterwidth, epswidth);

    return 0;
}
