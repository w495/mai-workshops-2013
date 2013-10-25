#include "lib/libcalc.h"

#define FA_INDEX 1
#define OP_INDEX 2
#define SA_INDEX 3

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


