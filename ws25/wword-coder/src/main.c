#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> // для memset и memcmp
#include <wchar.h>  // для работы с unicode
#include <wctype.h> // для iswspace
#include <locale.h> // во избежание "крокозяблей" на выводе

#include "stree.h"

int main(int argc, char* argv[]) {
    if (! setlocale(LC_ALL, "ru_RU.utf8"))
        // Используем Linux с Unicode UTF8 консолью
        return 1;
    FILE* input  = stdin;
    FILE* cipher = stdout;
    FILE* keys   = stderr;
    if(argc > 1){
        if(!(input = fopen(argv[1], "r"))){
            perror(argv[1]);
            return 1;
        }
    }
    if(argc > 2){
        if(!(cipher = fopen(argv[2], "w"))){
            perror(argv[2]);
            return 1;
        }
    }
    if(argc > 3){
        if(!(keys = fopen(argv[3], "w"))){
            perror(argv[3]);
            return 1;
        }
    }
    xresult_t xresult = wword_scan(input);
    stree_t* stree  = stree_create();
    size_t counter  = 0;
    size_t position = 0;
    while(!feof(input)){
        if(xresult.isok){
            wword_t* wword = (wword_t*)xresult.value;
            stree = stree_insert_or_update(stree, wword, position, &counter);
        }
        xresult = wword_scan(input);
        position++;
    }
    stree_print(stree, keys);
    rewind(input);
    xresult = wword_scan(input);
    while(!feof(input)){
        if(xresult.isok){
            wword_t* wword = (wword_t*)xresult.value;
            stree_t* xstree = stree_find(stree, wword);
            if(wword->eoln){
                fwprintf(cipher, L"\n");
            }
            else{
                fwprintf(cipher, L"%lx ", xstree->counter);
            }
        }
        xresult = wword_scan(input);
    }
    return 0;
}

