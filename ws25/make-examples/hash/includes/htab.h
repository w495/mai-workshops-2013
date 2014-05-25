#ifndef __HASH_HTAB_H__
#define __HASH_HTAB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "node.h"

#define HTAB_INIT_SIZE 16561

typedef struct {

    size_t size;        /** Количество элементов в таблице   **/

    node_t **data;      /** Массив указателей на ячейки      **/

    bool *_used;        /** Массив с флагами использования   **/

    size_t _idx;        /** Индекс рехеширования             **/

    size_t _cap;        /** Реальный размер таблицы          **/
} htab_t;


/**
 * @fn  Создает хеш-таблицу.
 *      Выделяет память. Инициализирует поля структуры.
 */
htab_t *htab_create();

/**
 *  @fn Возвращает количество элементов в таблице.
 */
size_t htab_get_size(htab_t * const);

/**
 *  @fn Возвращает размер таблицы.
 */
size_t htab_get_cap(htab_t * const);


/**
 *  @fn Добавляет в таблицу node.
 *      На этот момент Node уже должен быть создан.
 *      Функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_addnode(htab_t *, node_t * const);

/**
 *  @fn Ищет node по таблице.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Искомое значение возвращается в node->value.
 *      Сама функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_findnode(htab_t * const, node_t *);

/**
 *  @fn Удаляет из таблицы элемент с ключом от node.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Сама функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_delnode(htab_t *, node_t *);

/**
 *  @fn Ищет node по таблице.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Возвращает hash для ключа node
 */
hash_t htab_findhash(htab_t * const, node_t *);

/**
 *  @fn Выводит хеш-таблицу в файловый поток stream в формате JSON.
 */
int htab_tojson(FILE *, htab_t *);

/**
 *  @fn Выводит хеш-таблицу в файловый поток stream в формате XML.
 */
int htab_toxml(FILE *, htab_t *);

/**
 *  @fn Удаляет хеш-таблицу. Освобождает память.
 */
void htab_destroy(htab_t *);

/**
 *  @fn Производит рехеширование.
 *      Реализовано квадратичное рехеширование.
 */
hash_t rehash(hash_t, size_t f_id, size_t table_size);


#endif /* __HASH_HTAB_H__ */
