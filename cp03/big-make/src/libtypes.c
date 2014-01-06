/**
 * @file    libtypes.с
 *          Файл с кодом для пакета libtypes.
 * 
 * @package libtypes
 *          Работа с типами данных.
 */ 

/*
 * Подключаем только один заголовочный файл. 
 * В нем иже сделаны все нужные определения и включения.
 */ 
#include "libtypes.h"

/**
 * @fn  Вычисляет количество десятичных цифр для числа типа `step_t`.
 */ 
int steplen(step_t step){
    return ceil(log10(step) + 1);
}

/**
 * @fn  Вычисляет количество десятичных цифр для числа типа `iter_t`.
 */ 
int iterlen(iter_t iter){
    return ceil(log10(iter) + 1);
}

/**
 * @fn  Вычисляет количество десятичных дробных цифр для числа типа `real_t`.
 *      Используется для определения длины машинного эпсилон.
 */
int epslen(real_t eps){
    return ceil(-log10(eps));
}
