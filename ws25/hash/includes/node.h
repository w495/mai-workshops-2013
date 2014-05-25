#ifndef __HASH_NODE_H__
#define __HASH_NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#define NODE_BLOCKSIZE 16

/**
 * @typedef Тип хеш-чисел
 */
typedef size_t hash_t;


/**
 *  @typedef Тип для ячейки хеш-таблицы.
 */
typedef struct {

    char *key;          /** Ключ **/

    char *value;        /** Значение **/

    char *_buffer;      /** Внутренний буфер для удобства считывания **/
} node_t;


/**
 *  @fn Создает элемент хеш-таблицы.
 *      Инициализирует поля структуры.
 */
node_t *node_create();

/*
 * Опишем функции, которые будут инкапсулировать
 * в себя внутренне устройство node_t.
 * Это сделано для того, чтобы функции htab_ ничего не знали про элемент.
 * В случае, если мы захотим поменять node,
 * нам ничего не придется переделывать.
 */

char *node_get_key(node_t *);

char *node_get_value(node_t *);

void node_set_key(node_t *, char *);

void node_set_value(node_t *, char *);

/**
 *  @fn Считывает ключ и значение элемента таблицы со стандартного ввода.
 */
int node_fscan_all(FILE *, node_t *);

/**
 *  @fn Считывает ключ элемента таблицы со стандартного ввода.
 */
int node_fscan_key(FILE *, node_t *);

/**
 *  @fn Вычисляет хеш для ключ элемента таблицы.
 */
hash_t node_hashing(node_t * const, size_t table_size);

/**
 *  @fn Удаляет элемент хеш-таблицы.
 *      Освобождает память.
 */
void node_destroy(node_t * node);


#endif /* __HASH_NODE_H__ */
