#ifndef __LIBTYPE_H__04463696__
#define __LIBTYPE_H__04463696__

/**
 * @file    types.h
 *          Заголовочный файл с описанием типов данных,
 *          и функций по проверки принадлежности.
 *
 * @package types
 *          Работа с типами данных.
 */

/**
 * @typedef Строка для имени.
 */
typedef char  name_t[32];

/**
 * @typedef Строка для номера группы.
 */
typedef char  group_t[8];

/**
 * @typedef Описание логического типа.
 */
typedef enum {FALSE, TRUE} bool_t;

/**
 * @typedef Описание логического типа, для обозначения пола.
 *          Если явно не использовать приведения типов,
 *          то числовые константы будут выбраны произвольно
 *          на усмотрение компилятора.
 */
typedef enum {MALE = (int)'m', FEMALE = (int)'f'} gender_t;

/**
 * @typedef Тип сдал \ не сдал.
 */
typedef enum {NOT_PASSED = 0, PASSED = 1} passed_t;

/**
 * @typedef Тип оценки. Считаем, что оценки начинаются с 2.
 */
typedef enum {BAD = 2, SATISFACTORY = 3, GOOD = 4, EXCELLENT = 5} mark_t;


/**
 * @fn Проверяет, что переданное значение удовлетворяет типу пола.
 */
bool_t is_gender_type(gender_t gender);

/**
 * @fn Проверяет, что переданное значение удовлетворяет типу сдал \ не сдал.
 */
bool_t is_passed_type(passed_t passed);

/**
 * @fn Проверяет, что переданное значение удовлетворяет типу оценки.
 */
bool_t is_mark_type(mark_t mark);


#endif /* __LIBTYPE_H__04463696__ */ 
