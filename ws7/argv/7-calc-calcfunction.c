#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define OP_SUM '+'
#define OP_SUB '-'
#define OP_DIV '/'
#define OP_MUL 'x'
#define OP_POW '^'

#define FA_INDEX 1
#define OP_INDEX 2
#define SA_INDEX 3

/**
 * @fn Gets number from argv
 * @WARNING: We only deal with positive numbers. (0_o)
 * @WARNING: We have possible problem with exit(1).
 **/
int getnum(char*);

/**
 * @fn Calculates operation `op` with to int args.
 * @WARNING: We have possible problem with exit(1).
 **/
int calc(char, int, int);

/**
 * @fn Prints error message.
 **/
void error(char*);

int main(int argc, char* argv[], char* env[]){
  int firstarg; 
  int secondarg;
  int result;
  char op;
  
  if(argc != 4){
    error("wrong usage: argc must be 4\n");
    return 1;
  }
  
  firstarg  = getnum(argv[FA_INDEX]);
  secondarg = getnum(argv[SA_INDEX]);
  op = argv[OP_INDEX][0];

  result = calc(op, firstarg, secondarg);
  printf("%d\n", result );
  return 0;
}


/**
 * @fn Calculates operation `op` with to int args.
 **/
int calc(char op, int firstarg, int secondarg){
  int result = 0;
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
      int i;
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
int getnum(char* arg){
  int i;
  int len;
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
  return atoi(arg);
}

/**
 * @fn Prints error message.
 **/
void error(char* msg){
  printf("Error: %s\n", msg);
}
