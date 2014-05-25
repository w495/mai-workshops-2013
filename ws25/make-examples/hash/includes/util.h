#ifndef __HASH_UTIL_H__
#define __HASH_UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @fn  Считывает строку произвольного размера.
 *      Производит выделение памяти для строки.
 *      Строка считывается по блокам.
 *      В качестве параметров задаются входной поток и размер блока.
**/
char *afgets(FILE * stream, const size_t block_size);


#endif /* __HASH_UTIL_H__ */
