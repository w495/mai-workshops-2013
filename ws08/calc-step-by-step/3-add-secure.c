#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char* argv[], char* env[]){
  int firstarglen;
  int secondarglen;
  int i;

  if(argc != 3){
    printf("wrong usage:  argc = %d\n", argc);
    return 1;
  }

  firstarglen = strlen(argv[1]);  
  for(i = 0 ; i != firstarglen; ++i){
    /**
     * WARNING: we deal with just positive numbers.
     **/
    if(!isdigit(argv[1][i])){
      printf("wrong usage: argv[1] is not digit\n");
      return 1;
    }
  }

  secondarglen = strlen(argv[2]);
  for(i = 0 ; i != secondarglen; ++i){
    /**
     * WARNING: we deal with just positive numbers.
     **/
    if(!isdigit(argv[2][i])){
      printf("wrong usage: argv[2] is not digit\n");
      return 1;
    }
  }
  
  printf("%d\n", atoi(argv[1]) + atoi(argv[2]));
  return 0;
}
