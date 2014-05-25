
/** 
 * STANDART CALCULATOR
 *
 *      Simple project for С beginners. It demonstrates usage 
 *      of programm primitives, modules and `makefile`.
 *      Programme reads from the stdin-stream until end of file.
 *      It is very similar to bc, but has only 5 operations:
 *          * addition,         denoted as '+';
 *          * subtraction,      denoted as '-';
 *          * multiplication,   denoted as 'x'
 *          * division,         denoted as '/'
 *          * power,            denoted as  '^'
 *      You cannot input negative number.
 *      Operation arguments can be only natural numbers or zero, 
 *      whereas results can be integers.
 * 
 *      Example:
 *
 *          | $> ./stdcalc
 *          | 10 + 42
 *          | 52
 *          | 10 - 2
 *          | 8
 *          | 100 x 2
 *          | 200
 *          | $>
 * 
**/

/*
 * We include a single header file. 
 * It has already made ​​all the necessary definitions and inclusion.
 */
#include "lib/libcalc.h"

int main() {
    int firstarg;
    int secondarg;
    int result;
    char op;

    while (scanf("%d %c %d", &firstarg, &op, &secondarg) != EOF) {
        /*
         * Function calc is from libcalc.
         */
        result = calc(op, firstarg, secondarg);
        printf("%d\n", result);
    }

    return 0;
}
