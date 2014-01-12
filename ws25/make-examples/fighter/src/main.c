/**
 *  © Ilya w495 Nikitin 2013, MAI
 *  Workshop 8. «Motion of a point», Scenario 26. Normal version.
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

#include "lib/libbiz.h"

const size_t STEPS = 50;

const coord_t I_0 = -10;
const coord_t J_0 = -10;
const coord_t L_0 =  6;

const coord_t ELLIPSE_X0 = 20;
const coord_t ELLIPSE_Y0 = 0;

const coord_t ELLIPSE_XDIAG = 10;
const coord_t ELLIPSE_YDIAG = 5;


int main(int argc, char* argv[], char* env[]){
    coord_t i = I_0;
    coord_t j = J_0;
    coord_t l = L_0;
    coord_t i_tmp = 0;
    coord_t j_tmp = 0;
    coord_t l_tmp = 0;
    coord_t ex0 = ELLIPSE_X0;
    coord_t ey0 = ELLIPSE_Y0;
    coord_t exd = ELLIPSE_XDIAG;
    coord_t eyd = ELLIPSE_YDIAG;

    bool_t isout = TRUE;
    size_t k = 0;

    isout = out_of_ellipse(i, j, ex0, ey0, exd, eyd);

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
        isout = out_of_ellipse(i, j, ex0, ey0, exd, eyd);
        
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
