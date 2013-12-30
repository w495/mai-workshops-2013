#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#include <errno.h>

#define OP_SUM '+'
#define OP_SUB '-'
#define OP_DIV '/'
#define OP_MUL 'x'
#define OP_POW '^'

#define FA_INDEX 1
#define OP_INDEX 2
#define SA_INDEX 3


typedef double number_t;


/**
 * @fn Gets number from argv
 * @WARNING: We only deal with positive numbers. (0_o)
 * @WARNING: We have possible problem with exit(1).
 **/
number_t  getnum(char*);

/**
 * @fn Calculates operation `op` with to number_t args.
 * @WARNING: We have possible problem with exit(1).
 **/
number_t calc(char, number_t, number_t);

/**
 * @fn Prints error message.
 **/
void error(char*);

int main(int argc, char* argv[], char* env[]){
  number_t firstarg; 
  number_t secondarg;
  number_t result;
  char op;
  
  if(argc != 4){
    error("wrong usage: argc must be 4\n");
    return 1;
  }
  
  firstarg  = getnum(argv[FA_INDEX]);
  secondarg = getnum(argv[SA_INDEX]);
  op = argv[OP_INDEX][0];
  result = calc(op, firstarg, secondarg);
  printf("%f\n", result );
  if(errno)
    perror("Err:");
  return 0;
}


/**
 * @fn Calculates operation `op` with to number_t args.
 **/
number_t calc(char op, number_t firstarg, number_t secondarg){
  number_t result = 0;
  switch(op){
    case OP_SUM: 
      result = firstarg + secondarg; 
      break;
    case OP_SUB: 
      result = firstarg - secondarg; 
      break;
    case OP_DIV: 
      if(0 == secondarg){
        error("division by zero");
        /**
         * @WARNING: Possible problem. 
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
      number_t i;
      result = 1;
      for(i = 0 ; i != secondarg; ++i)
        result *= firstarg ; 
    }
    break;
    default: 
      error("unknown operation");
      /**
       * @WARNING: Possible problem. 
       * Gives a damn about that now. (^_^)
       **/
      exit(1);
  };
  return result;
}

/**
 * @fn Gets number from argv
 **/
number_t getnum(char* arg){
  /**
   *  @INFO: size_t != int
  */ 
  size_t i; 
  /**
   *  @INFO: size_t != int
  */ 
  size_t len;
  len = strlen(arg);  
  for(i = 0 ; i != len; ++i){
    /**
     * @WARNING: We only deal with positive numbers. (0_o)
     **/
    if(!isdigit(arg[i])){
      error("wrong usage: argvs is not numbers");
      /**
       * @WARNING: Possible problem. 
       * Gives a damn about that now. (^_^)
       **/
      exit(1);
    }
  }
  return atof(arg);
}

/**
 * @fn Prints error message.
 **/
void error(char* msg){
  printf("Error: %s\n", msg);
}
