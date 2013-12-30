#include<stdio.h>

int main(int argc, char* argv[], char* env[]){
  printf("What the Hell!\n I'm %s \n", argv[0]);
  while(number != argc){
    printf("argv[%d] = %s;\n", number, argv[number]);
    /**
       number = number + 1;
       number += number;
    **/
    number++;
  }
  return 0;
}
