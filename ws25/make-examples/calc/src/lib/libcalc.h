#ifndef __LIBCALC__
#define __LIBCALC__

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define OP_SUM '+'
#define OP_SUB '-'
#define OP_DIV '/'
#define OP_MUL 'x'
#define OP_POW '^'

/**
 * @fn Gets number from argv
 * WARNING: We only deal with positive numbers. (0_o)
 * WARNING: We have possible problem with exit(1).
 **/
int getnum(char *);

/**
 * @fn Calculates operation `op` with to int args.
 * WARNING: We have possible problem with exit(1).
 **/
int calc(char, int, int);

/**
 * @fn Prints error message.
 **/
void error(char *);

#endif /* __LIBCALC__ */
