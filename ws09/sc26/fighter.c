/**
 *  © Ilya w495 Nikitin 2013, MAI
 *  Workshop 9. «Motion of a point», Scenario 26. Normal version.
 * 
 * The ellipse is centered at the point (20, 0), 
 * passing through the point (10, 0), (30, 0), (20, 5) and (20, -5).
 * 
 *      i_0 = −10, j_0 = −10, l_0 = 6,
 *      i_{k+1} =   |max(
 *                      min(i_k + j_k, i_k + l_k) mod 30, 
 *                      max(i_k + l_k, j_k + k) mod 25
 *                  )|,
 *      j_{k+1} =   |i_k + k| mod 10 + |j_k + k| mod 10 + |l_k + k| mod 10,
 *      l_{k+1} =   (i_k^3 + j_k^3 + l_k^3 − k) mod 35. 
 * 
 */ 

#include <stdio.h>

typedef int coord_t;

const size_t STEPS = 50;

const coord_t I_0 = -10;
const coord_t J_0 = -10;
const coord_t L_0 =   6;

const coord_t ELLIPSE_X0 = 20;
const coord_t ELLIPSE_Y0 =  0;

const coord_t ELLIPSE_XDIAG = 10;
const coord_t ELLIPSE_YDIAG =  5;

/**************************************************************************
 * <libmath>
 **************************************************************************/

typedef enum {FALSE = 0, TRUE = 1} bool_t;

coord_t div(coord_t, coord_t);

coord_t mod(coord_t, coord_t);

void test_mod();

coord_t power(coord_t, size_t);

coord_t max(coord_t, coord_t);

coord_t min(coord_t, coord_t);

coord_t norm(coord_t);

/**************************************************************************
 * </libmath>
 **************************************************************************/

/**************************************************************************
 * <libbiz>
 **************************************************************************/

coord_t ellipse_common(
    coord_t x, 
    coord_t y, 
    coord_t x0, 
    coord_t y0, 
    coord_t a, 
    coord_t b
);

coord_t ellipse(coord_t, coord_t);

bool_t out_of_ellipse(coord_t, coord_t);

coord_t next_i(
    coord_t i, 
    coord_t j, 
    coord_t l,
    size_t k
);

coord_t next_j(
    coord_t i, 
    coord_t j, 
    coord_t l,
    size_t k
);

coord_t next_l(
    coord_t i, 
    coord_t j, 
    coord_t l,
    size_t k
);

coord_t next_k(
    coord_t i, 
    coord_t j, 
    coord_t l,
    size_t k
);

/**************************************************************************
 * </libbiz>
 **************************************************************************/

int main(int argc, char* argv[], char* env[]){

    coord_t i = I_0;
    coord_t j = J_0;
    coord_t l = L_0;
    coord_t i_tmp = 0;
    coord_t j_tmp = 0;
    coord_t l_tmp = 0;

    bool_t isout = TRUE;
    size_t k = 0;

    /**
    /* Call debug function 
     */ 
    test_mod();
    isout = out_of_ellipse(i, j);
    
    /** 
     * Print debug message to `stderr`.
     */ 
    fprintf(stderr, "%lu) i = %d j = %d l = %d\n",  k, i, j, l);
    while((k < STEPS) && isout){
        i_tmp = next_i(i, j, l, k);
        j_tmp = next_j(i, j, l, k);
        l_tmp = next_l(i, j, l, k);
        /* here k = next_k is the sim to k++ */
        k = next_k(i, j, l, k);
        i = i_tmp;
        j = j_tmp;
        l = l_tmp;
        isout = out_of_ellipse(i, j);
        /** 
         * Print debug message to `stderr`.
         */ 
        fprintf(stderr, "%lu) i = %d j = %d l = %d\n",  k, i, j, l);
    };

    if(isout){
        printf("No\n%d %d %d\n", i, j, l);
    }
    else{
        printf("Yes\n%d %d %d\n", i, j, l);
    }

    return 0;
}

/**************************************************************************
 * <libmath>
 **************************************************************************/

coord_t div(coord_t first, coord_t second){
    /**
     *  10 /  3 =  3
     * -10 /  3 = -4
     *  10 / -3 = -4
     * -10 / -3 =  3
     **/ 
    if (((0 < first) && (0 < second)) || ((first < 0) && (second < 0)))
        return first / second;
    return first / second - 1;
}

coord_t mod(coord_t first, coord_t second){
    return  first - div(first, second) * second;
    
     /** 
     *  Other versions of this function without calling div:
     * 
     *      Direct:
     * 
     *          coord_t remainder;
     *          if(0 > second){
     *              remainder = -first % -second;
     *              if( 0 > remainder)
     *                  remainder -= second;
     *              remainder = -remainder;
     *          }
     *          else{
     *              remainder = first % second;
     *              if( 0 > remainder)
     *                  remainder += second;
     *          }
     *          return remainder;
     *       
     *      Сompact:
     *  
     *          coord_t remainder = first % second;
     *          return  (0 > second) ? 
     *              -mod(-first, -second) 
     *              : ((0 > remainder) ? remainder + second: remainder);
     *
     *      Tricky:
     *      
     *          return (first % second + second) % second;
     */
}

void test_mod(){
    printf(" 10 %%  3 == %d\n",      10 % 3);
    printf("-10 %%  3 == %d\n",     -10 % 3);
    printf(" 10 %% -3 == %d\n",      10 % -3);
    printf("-10 %% -3 == %d\n\n",   -10 % -3);
    printf("mod( 10,  3) == %d\n",   mod(10, 3));
    printf("mod(-10,  3) == %d\n",   mod(-10, 3));
    printf("mod( 10, -3) == %d\n",   mod(10, -3));
    printf("mod(-10, -3) == %d\n\n", mod(-10, -3));
}

coord_t power(coord_t val, size_t p){
    size_t i;
    coord_t result = 1;
    for(i = 0 ; i != p; ++i)
        result *= val ; 
    return result;
}

coord_t max(coord_t first, coord_t second){
    if(first > second)
        return first;
    return second;
}

coord_t min(coord_t first, coord_t second){
    if(first < second)
        return first;
    return second;
}

coord_t norm(coord_t arg){
    if(0 < arg)
        return arg;
    return -arg;
}

coord_t sign(coord_t arg){
    if(0 == arg )
        return 0;
    if(0 < arg )
        return 1;
    return -1;
}

/**************************************************************************
 * </libmath>
 **************************************************************************/

/**************************************************************************
 * <libbiz>
 **************************************************************************/

coord_t ellipse_common(
    coord_t x, 
    coord_t y, 
    coord_t x0, 
    coord_t y0, 
    coord_t a, 
    coord_t b
){
    return (power(x - x0, 2) / power(a, 2)) + (power(y - y0, 2) / power(b, 2));
}

coord_t ellipse(coord_t x, coord_t y){
    return ellipse_common(
        x, 
        y, 
        ELLIPSE_X0, 
        ELLIPSE_Y0, 
        ELLIPSE_XDIAG, 
        ELLIPSE_YDIAG
    );
}

bool_t out_of_ellipse(coord_t x, coord_t y){
    if(1 < ellipse(x, y))
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

/**************************************************************************
 * </libbiz>
 **************************************************************************/
