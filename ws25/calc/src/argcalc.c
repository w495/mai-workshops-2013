
/** 
 * ARGUMENT CALCULATOR
 * 
 *      Simple project for С beginners. It demonstrates usage 
 *      of programm primitives, modules and `makefile`.
 *      It uses command-line arguments like this:
 *
 *          | $> ./argcalc 2 + 2
 *          | 4
 *          | $> ./argcalc 2 - 10
 *          | -8
 *          | $> 
 * 
 *      Calculator has only 5 operations:
 *          * addition,         denoted as '+';
 *          * subtraction,      denoted as '-';
 *          * multiplication,   denoted as 'x'
 *          * division,         denoted as '/'
 *          * power,            denoted as  '^'
 *      You cannot input negative number.
 *      Operation arguments can be only natural numbers or zero, 
 *      whereas results can be integers.
**/

/*
 * We include a single header file. 
 * It has already made ​​all the necessary definitions and inclusion.
 */
#include "lib/libcalc.h"

#define FA_INDEX 1
#define OP_INDEX 2
#define SA_INDEX 3

int main(int argc, char *argv[], char *env[]) {
    int firstarg;
    int secondarg;
    int result;
    char op;

    if (argc != 4) {
        error("wrong usage: argc must be 4\n");
        return 1;
    }

    firstarg = getnum(argv[FA_INDEX]);
    secondarg = getnum(argv[SA_INDEX]);
    op = argv[OP_INDEX][0];

    /*
     * Function calc is from libcalc.
     */
    result = calc(op, firstarg, secondarg);
    printf("%d\n", result);
    return 0;
}
