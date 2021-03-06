#ifndef __MAIN_H__320586560__
#define __MAIN_H__320586560__

/**
 * @file    main.h
 *          Заголовочный файл с константами настроек проекта.
 *          Начальная и конечные точки, коэффициент сходимости и пр.
 * 
 * @package main
 *          Основная логика программы.
 */ 

/*
 * Подключаем заголовочный файл 
 * с описанием типов `step_t`, `iter_t`, `real_t`.
 * и функциями вычисления их длины.
 */ 
#include "libtypes.h"

/*
 * Подключаем заголовочный файл 
 * с описанием функций вычисления целевой функции и ее численного приближения.
 */ 
#include "libfunc.h"

/*
 * Подключаем заголовочный файл 
 * с описанием функций красивого вывода таблицы результатов.
 */ 
#include "libformat.h"

/**
 * Начальная точка.
 */
const real_t START_X = 0.1;

/**
 * Конечная точка.
 */
const real_t STOP_X = 0.6;

/**
 * Количество итераций по Тейлору.
 */
const iter_t ITER_LIMIT = 100;

/**
 * Коэффициент сходимости. Подбирался экспериментально.
 */
const real_t COEF = 100.0;

#endif /* __MAIN_H__320586560__ */
