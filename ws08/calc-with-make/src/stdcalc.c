#include "lib/libcalc.h"

int main(int argc, char* argv[], char* env[]){
  int firstarg; 
  int secondarg;
  int result;
  char op;
  
  

  while(scanf("%d %c %d", &firstarg, &op, &secondarg) != EOF){
    result = calc(op, firstarg, secondarg);
    printf("%d\n", result );  
  }

  return 0;
}
