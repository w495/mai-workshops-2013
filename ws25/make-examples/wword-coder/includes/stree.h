#ifndef __STREE_H__
#define __STREE_H__

///
/// Вариант дерева поиска
///

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> // для memset и memcmp
#include <wchar.h>  // для работы с unicode


#include "wword.h"

typedef struct stree {
    struct stree* left;
    struct stree* right;
    wword_t* value;
    size_t freq;        //  частота слова
    size_t counter;     //  номер слова среди уникальных
    size_t position;    //  номер слова среди не уникальных
} stree_t;


/// @fn Создает дерево
stree_t* stree_create();

/// @fn Добавляет в дерево узел.
/// Присваивает значение value, freq, counter и position.
/// Если такой узел в дереве уже есть, то увеличивает значение freq.
///
stree_t* stree_insert_or_update(stree_t*, wword_t*, size_t, size_t*);

/// @fn Возвращает узел с указанным ключом.
stree_t* stree_find(stree_t*, wword_t*);

/// @fn Рекурсивно удаляет дерево.
void stree_destroy(stree_t * stree);

/// @fn Печатает дерево с завершающим переводом строки.
void stree_print(stree_t* stree, FILE* output);

/// @fn Печатает дерево
void stree_print_(stree_t* stree, FILE* output);


#endif // __STREE_H__
