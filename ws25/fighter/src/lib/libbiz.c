#include "libbiz.h"

coord_t ellipse(
    coord_t x, 
    coord_t y, 
    coord_t x0, 
    coord_t y0, 
    coord_t a, 
    coord_t b
){
    return (power(x - x0, 2) / power(a, 2)) + (power(y - y0, 2) / power(b, 2));
}

bool_t out_of_ellipse(    
    coord_t x, 
    coord_t y, 
    coord_t x0, 
    coord_t y0, 
    coord_t a, 
    coord_t b
){
    if(1 < ellipse(x, y, x0, y0, a, b))
        return TRUE;
    return FALSE;
}

/**
 *  @fn Returns the value of
 *      |max(min(ik + jk, ik + lk) mod 30, max(ik + lk, jk + k) mod 25)|
 */
coord_t next_i(coord_t i, coord_t j, coord_t l, size_t k){
    return norm(
        max(
            mod(
                min(
                    i + j,
                    i + l
                ),
                30
            ),
            mod(
                max(
                    i + l,
                    j + k
                ),
                25
            )
        )
    );
}


/**
 *  @fn Returns the value of
 *      |ik + k| mod 10 + |jk + k| mod 10 + |lk + k| mod 10
 */
coord_t next_j(coord_t i, coord_t j, coord_t l, size_t k){
    return (
        mod(
            norm(i + k),
            10
        ) 
        + mod(
            norm(j + k),
            10
        )
        + mod(
            norm(l + k),
            10
        )
    );
}


/**
 *  @fn Returns the value of
 *      (ik3 + jk3 + lk3 − k) mod 35
 */
coord_t next_l(coord_t i, coord_t j, coord_t l, size_t k){
    return mod(
        power(i, 3)
        + power(j, 3)
        + power(l, 3)
        + k,
        35
    );
}

/**
 *  @fn Returns next k. The same as k++.
 */
coord_t next_k(coord_t i, coord_t j, coord_t l, size_t k){
    return k + 1;
}
