#ifndef __WWORD_H__
#define __WWORD_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> // для memset и memcmp
#include <wchar.h> // для работы с unicode
#include <wctype.h> // для iswspace

typedef struct {
    bool    isok;
    void*   value;
} xresult_t;


#define WWORD_STRING_SIZE 1024

typedef struct {
    size_t  size;
    bool    eoln;
    wchar_t* string;
} wword_t;

xresult_t wword_scan(FILE* input);

int wword_cmp(wword_t*, wword_t*);

#endif // __WWORD_H__
