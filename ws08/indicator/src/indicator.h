#include<stdio.h>


int _indicator(int, char, char, char, char, char);
int _mindicator(int i, char, char, char, char, char, char track);
int _findicator(FILE *, int, char, char, char, char, char);
int _fmindicator(FILE *, int, char, char, char, char, char, char track);



#define indicator_O_o(i) \
    _fmindicator(stderr, (i), '.', 'o', 'O', 'o', '.', '.');

/**
 * It is classical indicator as in FreeBSD
 *    -----
 *    ----\
 *    ----|
 *    ----/
 *    -----
 *    ------\    
**/
#define indicator_line(i) \
    _fmindicator(stderr, (i), '-', '\\', '|', '/',  '-', '-');


#define indicator_arrow(i) \
    _fmindicator(stderr, (i), '>', '|', '>', '|',  '>', '-');
