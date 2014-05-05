#ifndef __STREE_H__
#define __STREE_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> // для memset и memcmp
#include <wchar.h>  // для работы с unicode


#include "wword.h"

typedef struct stree stree_t;

typedef struct stree {
    stree_t* left;
    stree_t* right;
    wword_t* value;
    size_t freq;
    size_t counter;
    size_t position;
} stree_t;



stree_t* stree_create();

stree_t* stree_insert_or_update(stree_t*, wword_t*, size_t, size_t*);

stree_t* stree_find(stree_t*, wword_t*);

void stree_destroy(stree_t * stree);

void stree_print(stree_t* stree, FILE* output);

void stree_print_(stree_t* stree, FILE* output);


#endif // __STREE_H__
