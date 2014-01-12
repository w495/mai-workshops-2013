#ifndef __LIBBIZ_299080907__
#define __LIBBIZ_299080907___

#include "libmath.h"

coord_t ellipse(
    coord_t x, 
    coord_t y, 
    coord_t x0, 
    coord_t y0, 
    coord_t a, 
    coord_t b
);

bool_t out_of_ellipse(
    coord_t x, 
    coord_t y, 
    coord_t x0, 
    coord_t y0, 
    coord_t a, 
    coord_t b
);

/**
 *  @fn Returns the value of
 *      |max(min(ik + jk, ik + lk) mod 30, max(ik + lk, jk + k) mod 25)|
 */
coord_t next_i(
    coord_t i, 
    coord_t j, 
    coord_t l,
    size_t k
);

/**
 *  @fn Returns the value of
 *      |ik + k| mod 10 + |jk + k| mod 10 + |lk + k| mod 10
 */
coord_t next_j(
    coord_t i, 
    coord_t j, 
    coord_t l,
    size_t k
);

/**
 *  @fn Returns the value of
 *      (ik3 + jk3 + lk3 − k) mod 35
 */
coord_t next_l(
    coord_t i, 
    coord_t j, 
    coord_t l,
    size_t k
);

/**
 *  @fn Returns next k. The same as k++.
 */
coord_t next_k(
    coord_t i, 
    coord_t j, 
    coord_t l,
    size_t k
);

#endif /* __LIBBIZ_299080907___ */
