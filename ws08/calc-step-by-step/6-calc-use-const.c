#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define OP_SUM '+'
#define OP_SUB '-'
#define OP_DIV '/'
#define OP_MUL 'x'
#define OP_POW '^'


const int FA_INDEX = 1;
const int OP_INDEX = 2;
const int SA_INDEX = 3;


/**
 * @fn Gets number from argv
 * @WARNING: We only deal with positive numbers. (0_o)
 * @WARNING: We have possible problem with exit(1).
 **/
int getnum(char*);

int main(int argc, char* argv[], char* env[]){
  int firstarg; 
  int secondarg;
  int result;
  char op;
  
  if(argc != 4){
    printf("Error: wrong usage:  argc = %d\n", argc);
    return 1;
  }
  
  firstarg  = getnum(argv[FA_INDEX]);
  secondarg = getnum(argv[SA_INDEX]);
  op = argv[OP_INDEX][0];

  switch(op){
    case OP_SUM: 
      result = firstarg + secondarg; 
      break;
    case OP_SUB: 
      result = firstarg - secondarg; 
      break;
    case OP_DIV: 
      if(0 == secondarg){
        printf("Error: division by zero\n");
        return 1;
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
      printf("Error: unknown operation\n");
      return 1;
  };
  printf("%d\n", result );
  return 0;
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
      printf("Error: wrong usage: argvs is not numbers\n");
      /**
       * @WARNING: Possible problem. 
       * Gives a damn about that now. (^_^)
       **/
      exit(1);
    }
  }
  return atoi(arg);
}