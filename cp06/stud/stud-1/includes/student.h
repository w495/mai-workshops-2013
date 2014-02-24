#ifndef __STUDENT_H__643505802__
#define __STUDENT_H__643505802__

/**
 * @file    student.h
 *          Заголовочный файл с описанием структуры записи о студенте.
 *
 * @package student
 *          Работа со структурой студентов.
 */

/*
 * Подключаем описание функций с переменных количеством аргументов.
 */
#include <stdarg.h>

/*
 * Подключаем заголовочный файл, со строковыми функциями.
 */
#include <string.h>

/*
 * Подключаем заголовочный файл, стандартного ввода-вывода
 */
#include <stdio.h>

/*
 * Подключаем определения типов данных.
 */
#include "types.h"

typedef struct __student__ {
    size_t      number;
    gender_t    gender;
    group_t     group;
    name_t      name;
    passed_t    physical_culture;
    passed_t    english; 
    mark_t      mathematical_analysis;
    mark_t      discrete_mathematics;
    mark_t      linear_algebra;
    mark_t      informatics;
    mark_t      history;
} student_t;



student_t student_init(void);

/**
 * @fn  Считывает информацию о студенте из файла `infile`.
 *      Возвращает код ошибки или `1` если все хорошо.
 *      См. реализацию.
 */
int student_fscanf(FILE* infile, student_t* student_pointer);

/**
 * @fn  Считывает информацию о студенте из файла `stdin`.
 *      Возвращает код ошибки или `1` если все хорошо.
 */
int student_scanf(student_t* student_pointer);

/**
 * @fn  Выводит информацию о студенте в файл `outfile`.
 *      Возвращает код ошибки или `1` если все хорошо.
 *      См. реализацию.
 */
int student_fprintf(FILE* outfile, student_t* student_pointer);

/**
 * @fn  Выводит информацию о студенте в файл `stdout`.
 *      Возвращает код ошибки или `1` если все хорошо.
 */
int student_printf(student_t* student_pointer);

/**
 * ОТЛАДОЧНЫЕ ФУНКЦИИ С ПЕРЕМЕННЫМ ЧИСЛОМ АРГУМЕНТОВ.
 */

/**
 * @fn  Выводит отладочное сообщение в форматом `format` в файл `outfile`
 *      Собственный аналог `printf`.
 */
int __student_vfprintf(FILE* outfile, const char* format, ... );

/**
 * @fn  Выводит сообщение об ошибке в формате `format` в файл `outfile`.
 *      Собственный аналог `printf`.
 *      При этом, параметры codefile, codeline, codefunction,
 *      являются обязательными, в отличие от `...`.
 *      Эти параметры на формат вывода не влияют.
 */
int __student_ferror(
    FILE* outfile,              /* Куда выводим                     */
    const char* codefile,       /* Файл с исходным кодом            */
    int codeline,               /* Номер строки в исходниках        */
    const char* codefunction,   /* Название функции в исходниках    */
    const char* format,         /* Формат вывода                    */
    ...                         /* Необязательные аргументы         */
);

/**
 * МАКРОСЫ С ПЕРЕМЕННЫМ ЧИСЛОМ АРГУМЕНТОВ.
 */

/**
 * @fn  Выводит отладочное  сообщение на `stderr`.
 *      Внутри вызывается функция `__student_vfprintf`.
 */
#define __STUDENT_PROMPT(...)   \
        __student_vfprintf (    \
            stderr,             \
            ##__VA_ARGS__       \
        )

/**
 * @fn  Выводит сообщение об ошибке на `stderr`.
 *      Внутри вызывается функция `__student_ferror`,
 *      файл с исходным кодом, номер строки и название функции
 *      подставляются соответственно на этапе компиляции.
 */
#define __STUDENT_ERROR(...)    \
        __student_ferror   (    \
            stderr,             \
            __FILE__,           \
            __LINE__,           \
            __FUNCTION__,       \
            ##__VA_ARGS__       \
        )



#endif /* __STUDENT_H__643505802__ */
