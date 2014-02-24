/**
 * @file    types.с
 *          Файл с кодом для пакета types.
 *
 * @package types
 *          Работа с типами данных.
 */

/*
 * Подключаем только один заголовочный файл.
 * В нем иже сделаны все нужные определения и включения.
 */
#include "types.h"

/**
 * @fn Проверяет, что переданное значение удовлетворяет типу пола.
 */
bool_t is_gender_type(gender_t gender){
    if( (MALE   == gender) ||
        (FEMALE == gender))
        return TRUE;
    return FALSE;
}

/**
 * @fn Проверяет, что переданное значение удовлетворяет типу сдал \ не сдал.
 */
bool_t is_passed_type(passed_t passed){
    if( (NOT_PASSED == passed) ||
        (PASSED     == passed))
        return TRUE;
    return FALSE;
}

/**
 * @fn Проверяет, что переданное значение удовлетворяет типу оценки.
 */
bool_t is_mark_type(mark_t mark){
    if( (BAD            == mark)    ||
        (SATISFACTORY   == mark)    ||
        (GOOD           == mark)    ||
        (EXCELLENT      == mark))
        return TRUE;
    return FALSE;
} 
