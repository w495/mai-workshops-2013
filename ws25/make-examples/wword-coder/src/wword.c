#include "wword.h"

xresult_t xresult_create(){
    xresult_t res;
    res.isok = false;
    return res;
}

xresult_t wword_scan(FILE* input) {
    xresult_t xresult = xresult_create();

    wword_t* this = malloc(sizeof(wword_t));
    this->string = malloc(sizeof(wchar_t) * (WWORD_STRING_SIZE + 1));
    this->eoln = false;

    wchar_t wchar = getwc(input);
    size_t counter = 0;

    if(iswalnum(wchar))
        while (iswalnum(wchar)){
            this->string[counter] = towlower(wchar);
            wchar = getwc(input);
            counter++;
            if(false == xresult.isok)
                xresult.isok = true;
        }
    else if(iswpunct(wchar)) {
        this->string[counter] = wchar;
        counter++;
        xresult.isok = true;
    }
    else if('\n' == wchar) {
        this->string[counter] = wchar;
        this->eoln = true;
        counter++;
        xresult.isok = true;
    }

    this->size = counter;
    this->string[counter] = '\0';
    xresult.value = this;
    return xresult;
}


int wword_cmp(wword_t* this, wword_t* other) {
    return memcmp (this->string, other->string, WWORD_STRING_SIZE);
}
