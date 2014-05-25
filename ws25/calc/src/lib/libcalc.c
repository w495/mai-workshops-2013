#include "libcalc.h"

/**
 * @fn Calculates operation `op` with to int args.
 **/
int calc(char op, int firstarg, int secondarg) {
    int result = 0;

    switch (op) {
        case OP_SUM:
            result = firstarg + secondarg;
            break;
        case OP_SUB:
            result = firstarg - secondarg;
            break;
        case OP_DIV:
            if (0 == secondarg) {
                error("division by zero");

        /**
         * WARNING: Possible problem. 
         * Gives a damn about that now. (^_^)
         **/
                exit(1);
            }
            else
                result = firstarg / secondarg;
            break;
        case OP_MUL:
            result = firstarg * secondarg;
            break;
        case OP_POW:
        {
            int i;

            result = 1;
            for (i = 0; i != secondarg; ++i)
                result *= firstarg;
        }
            break;
        default:
            error("unknown operation");

      /**
       * WARNING: Possible problem. 
       * Gives a damn about that now. (^_^)
       **/
            exit(1);
    };
    return result;
}

/**
 * @fn Gets number from argv
 **/
int getnum(char *arg) {
    int i;
    int len;

    len = strlen(arg);
    for (i = 0; i != len; ++i) {

    /**
     * WARNING: We only deal with positive numbers. (0_o)
     **/
        if (!isdigit(arg[i])) {
            error("wrong usage: argvs is not numbers");

      /**
       * WARNING: Possible problem. 
       * Gives a damn about that now. (^_^)
       **/
            exit(1);
        }
    }
    return atoi(arg);
}

/**
 * @fn Prints error message.
 **/
void error(char *msg) {
    printf("Error: %s\n", msg);
}
