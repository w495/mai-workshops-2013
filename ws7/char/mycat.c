#include<stdio.h>

int main(int argc, char* argv[], char* env[]){
  char symbol;
  symbol = getchar();
  while(symbol != EOF){
    putchar(symbol);
    symbol = getchar();
  }
  return 0;
}
