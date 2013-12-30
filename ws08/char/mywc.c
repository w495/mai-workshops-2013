#include<stdio.h>

int main(int argc, char* argv[], char* env[]){
  char symbol;
  int nchars = 0;
  int nspaces = 0;
  int nlines = 0;
  symbol = getchar();
  while(EOF != symbol){
    if(' ' == symbol)
      nspaces++;
    else if('\n' == symbol)
      nlines++;
    nchars++;
    symbol = getchar();
  }
  printf("\t%d\t%d\t%d\n", nlines, nspaces, nchars);
  return 0;
}
