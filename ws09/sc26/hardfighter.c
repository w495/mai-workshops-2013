/**
 *  © Ilya w495 Nikitin 2013, MAI
 *  Workshop 8. «Motion of a point», Scenario 26. Version with macroses.
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

#define STEPS   50

#define I_0 -10
#define J_0 -10
#define L_0   6

#define ELLIPSE_X0 20
#define ELLIPSE_Y0  0

#define ELLIPSE_XDIAG 10
#define ELLIPSE_YDIAG  5

/**************************************************************************/

#define coord_t int 
#define bool_t char
#define FALSE  0
#define TRUE   1

#define div(a, b) \
    (((((a) / (b))) > 0)?((a) / (b)) : (((a) / (b)) - 1))

#define mod(a, b) \
    (((a) % (b) + (b)) % (b))

/**
 * dirty hack!
 */

#define power2(a) \
    ((a) * (a))

#define power3(a) \
    ((a) * (a) * (a))

#define power(a, q) \
    ((2 == (q)) ? power2(a) : power3(a))

#define max(a,b) \
    ((((coord_t)(a)) > ((coord_t)(b)))?((coord_t)(a)) : ((coord_t)(b)))

#define min(a,b) \
    ((((coord_t)(a)) < ((coord_t)(b)))?((coord_t)(a)) : ((coord_t)(b)))
 
#define norm(a) \
    ((0 < ((coord_t)(a)))?((coord_t)(a)) : (-(coord_t)(a)))

/**************************************************************************/

#define ellipse_common(x, y, x0, y0, a, b)              \
    (                                                   \
        (power(((coord_t)(x) - (coord_t)(x0)), 2)       \
            / power((coord_t)(a), 2))                   \
        + (power(((coord_t)(y) - (coord_t)(y0)), 2)     \
            / power((coord_t)(b), 2))                   \
    )

#define ellipse(x, y)                               \
    ellipse_common(                                 \
        (coord_t)(x),                               \
        (coord_t)(y),                               \
        (coord_t)(ELLIPSE_X0),                      \
        (coord_t)(ELLIPSE_Y0),                      \
        (coord_t)(ELLIPSE_XDIAG),                   \
        (coord_t)(ELLIPSE_YDIAG)                    \
    )

#define out_of_ellipse(x, y) \
    (bool_t)((1 < (ellipse((coord_t)(x), (coord_t)(y)))) ? TRUE : FALSE)

/**
 *  @fn Returns the value of
 *      |max(min(ik + jk, ik + lk) mod 30, max(ik + lk, jk + k) mod 25)|
 */
#define next_i(i, j, l, k)                                      \
    norm(                                                       \
        max(                                                    \
            mod(                                                \
                min(                                            \
                    ((coord_t)(i) + (coord_t)(j)),              \
                    ((coord_t)(i) + (coord_t)(l))               \
                ),                                              \
                30                                              \
            ),                                                  \
            mod(                                                \
                max(                                            \
                    ((coord_t)(i) + (coord_t)(l)),              \
                    (coord_t)((coord_t)(j) + (size_t)(k))       \
                ),                                              \
                25                                              \
            )                                                   \
        )                                                       \
    )

/**
 *  @fn Returns the value of
 *      |ik + k| mod 10 + |jk + k| mod 10 + |lk + k| mod 10
 */
#define next_j(i, j, l, k)                                  \
    (coord_t)(                                              \
        mod(                                                \
            norm(((coord_t)(coord_t)(i) + (size_t)(k))),    \
            10                                              \
        )                                                   \
        + mod(                                              \
            norm((coord_t)((coord_t)(j) + (size_t)(k))),    \
            10                                              \
        )                                                   \
        + mod(                                              \
            norm((coord_t)(( coord_t)(l) + (size_t)(k))),    \
            10                                              \
        )                                                   \
    )

/**
 *  @fn Returns the value of
 *      (ik3 + jk3 + lk3 − k) mod 35
 */
#define next_l(i, j, l, k)                  \
    mod(                                    \
        (coord_t)(                          \
            power((coord_t)(i), 3)          \
            + power((coord_t)(j), 3)        \
            + power((coord_t)(l), 3)        \
            + (size_t)(k)                   \
        ),                                  \
        35                                  \
    )

/**
 *  @fn Returns next k. k = next(k) is the same as k++.
 */
#define next_k(i, j, l, k)  ((size_t)(k) + 1);

/**************************************************************************/

int main(int argc, char* argv[], char* env[]){
    coord_t i = I_0;
    coord_t j = J_0;
    coord_t l = L_0;
    coord_t i_tmp = 0;
    coord_t j_tmp = 0;
    coord_t l_tmp = 0;
    bool_t isout = TRUE;
    size_t k = 0;
    isout = out_of_ellipse(i, j);
    fprintf(stderr, "%lu) i = %d j = %d l = %d\n",  k, i, j, l);
    while((k < STEPS) && isout){
        i_tmp = next_i(i, j, l, k);
        j_tmp = next_j(i, j, l, k);
        l_tmp = next_l(i, j, l, k);
        k = next_k(i, j, l, k);
        i = i_tmp;
        j = j_tmp;
        l = l_tmp;
        isout = out_of_ellipse(i, j);
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
