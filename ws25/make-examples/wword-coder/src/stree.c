#include "stree.h"

stree_t* stree_create() {
    return NULL;
}

stree_t* stree_insert_or_update(
    stree_t* stree,
    wword_t* value,
    size_t position,
    size_t* ptrc
) {
    if(!stree){
        stree = malloc(sizeof(stree_t));
        stree->left = NULL;
        stree->right = NULL;
        stree->value = value;
        stree->freq = 1;
        stree->position = position;
        stree->counter = (*ptrc)++;

    }
    else if (wword_cmp(stree->value, value) < 0) {
        stree->left = stree_insert_or_update(stree->left, value, position, ptrc);
    }
    else if (wword_cmp(stree->value, value) > 0) {
        stree->right = stree_insert_or_update(stree->right, value, position, ptrc);
    }
    else {
        stree->freq += 1;
    }
    return stree;
}

stree_t* stree_find(stree_t* stree, wword_t* value) {
    if(stree){
        if (wword_cmp(stree->value, value) < 0) {
            return stree_find(stree->left, value);
        }
        else if (wword_cmp(stree->value, value) > 0) {
            return stree_find(stree->right, value);
        }
        else {
            return stree;
        }
    }
    return NULL;
}


void stree_destroy(stree_t * stree) {
    if (stree) {
        stree_destroy(stree->left);
        stree_destroy(stree->right);
        free(stree);
    }
}

void stree_print(stree_t* stree, FILE* output) {
    stree_print_(stree, output);
    fwprintf(output, L"\n");
}

void stree_print_(stree_t* stree, FILE* output) {
    if (stree) {
        wword_t* wword = stree->value;
        if(!wword->eoln)
            fwprintf(
                output,
                L"%ls %lx %lx %lx %lx\n",
                wword->string,
                wword->size,
                stree->freq,
                stree->counter,
                stree->position
            );
        stree_print_(stree->left, output);
        stree_print_(stree->right, output);
    }
}
