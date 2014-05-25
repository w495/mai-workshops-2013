#include "util.h"


/**
 * @fn  Считывает строку произвольного размера.
 *      Производит выделение памяти для строки.
 *      Строка считывается по блокам.
 *      В качестве параметров задаются входной поток и размер блока.
**/
char *afgets(FILE * stream, const size_t block_size) {
    char *result, *block, *temp;
    size_t size = block_size;
    size_t n = 0;

    result = block = (char *) malloc(size);
    if (!result)
        return NULL;
    *result = '\0';
    for (;;) {
        if (fgets(block, block_size, stream) == NULL)
            break;
        n += strlen(block);
        if (result[n - 1] == '\n')
            break;
        size += block_size;
        temp = (char *) realloc(result, size);
        if (temp == NULL)
            break;
        result = temp;
        block = result + n;
    }
    if (result[0] == '\0') {
        free(result);
        result = NULL;
    }
    return result;
}
