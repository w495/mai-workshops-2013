#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


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
    printf("wrong usage:  argc = %d\n", argc);
    return 1;
  }
  
  firstarg  = getnum(argv[1]);
  secondarg = getnum(argv[3]);
  op = argv[2][0];

  switch(op){
    case '+': result = firstarg + secondarg; break;
    case '-': result = firstarg - secondarg; break;
    case '/': result = firstarg / secondarg; break;
    case 'x': result = firstarg * secondarg; break;
    case '^': 
    {
      int i;
      result = 1;
      for(i = 0 ; i != secondarg; ++i)
        result *= firstarg ; 
    }
    break;
    default: result = 0;
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
