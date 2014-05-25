#ifndef __LIBBIZ_328426207__
#define __LIBBIZ_328426207___

#include <stddef.h>

typedef int coord_t;

typedef enum {FALSE = 0, TRUE = 1} bool_t;

coord_t div(coord_t, coord_t);

coord_t mod(coord_t, coord_t);

void test_mod();

coord_t power(coord_t, size_t);

coord_t max(coord_t, coord_t);

coord_t min(coord_t, coord_t);

coord_t norm(coord_t);



#endif /* __LIBBIZ_328426207___ */