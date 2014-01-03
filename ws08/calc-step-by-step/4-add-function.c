#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

/**
 * @fn Gets number from argv
 * @WARNING: We only deal with positive numbers. (0_o)
 * @WARNING: We have possible problem with exit(1).
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
      printf("wrong usage: argvs is not numbers\n");
      /**
       * @WARNING: Possible problem. 
       * Gives a damn about that now. (^_^)
       **/
      exit(1);
    }
  }
  return atoi(arg);
}

int main(int argc, char* argv[], char* env[]){
  int firstarg;
  int secondarg;
  
  if(argc != 3){
    printf("wrong usage:  argc = %d\n", argc);
    return 1;
  }
  
  firstarg  = getnum(argv[1]);
  secondarg = getnum(argv[2]);
  
  printf("%d\n", firstarg  + secondarg);
  return 0;
}
