#include "lib/libcalc.h"



int main(int argc, char* argv[], char* env[]){
  int firstarg; 
  int secondarg;
  int result;
  char op;

  scanf("%d %c %d", &firstarg, &op, &secondarg);
  
  result = calc(op, firstarg, secondarg);
  printf("%d\n", result );
  return 0;
}


