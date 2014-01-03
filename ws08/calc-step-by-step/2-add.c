#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[], char* env[]){
  printf("argc = %d\n", argc);
  if(argc == 3){
    printf("argv[1] = %s\n", argv[1]);
    printf("argv[2] = %s\n", argv[2]);
    printf(" %d \n", atoi(argv[1]) + atoi(argv[2]));
  }
  return 0;
}

