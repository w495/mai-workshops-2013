/**
 * @file    libfunc.с
 *          Файл с реализацией функций вычисления целевой 
 *          функции и ее численного приближения, 
 *          различных утилитарных функций.
 * 
 * @package libfunc
 *          Работа с целевой и численной функциями.
 */ 

/*
 * Подключаем только один заголовочный файл. 
 * В нем иже сделаны все нужные определения и включения.
 */ 
#include "libfunc.h"


/**
 * @fn Возвращает значение функции в точке `x`.
 */
real_t target_fuction(real_t x) {
    return (2 * x - 3) / ((x - 1) * (x - 1));
}

/**
 * @fn Возвращает значения n-го члена ряда Тейлора в точке `x`.
 */
real_t taylor_fuction(real_t x, iter_t n) {
    return -(n + 3) * rpow(x, n);
}

/**
 * @fn Возвращает модуль числа `x`.
 */
real_t rabs(real_t x) {
    if (x < 0)
        return -x;
    return x;
}

/**
 * @fn Возвращает модуль `n`-ную степень числа `x`.
 */
real_t rpow(real_t x, iter_t n) {
    iter_t i;
    real_t res = 1;

    for (i = 0; i != n; ++i) {
        res *= x;
    }
    return res;
}

/**
 * @fn  Приведения к 64-битам, на случай 80-битового вещественного регистра.
 *      См комментарий на http://k806.ru/infocourse/task3/
 */
real_t findent(real_t x) {
    return x;
}

/**
 * @fn Вычисляет и возвращает машинное эпсилон.
 */
real_t epsylone() {
    real_t eps = 1.0;

    while (findent(eps / 2 + 1) > 1)
        eps = eps / 2;
    return eps;
}
