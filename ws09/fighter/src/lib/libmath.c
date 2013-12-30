#include "libmath.h"


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

