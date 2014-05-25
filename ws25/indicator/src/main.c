#include<stdio.h>

#include"indicator.h"

#define DELAY_VALUE 20000000

#define CICLE_VALUE 80*4

void naive_delay(int time) {
    int i;

    for (i = 0; i != time; ++i) ;
}

int main() {
    while(1) {
        int i = 1;
        for (i = 0; i != CICLE_VALUE; ++i) {
            naive_delay(DELAY_VALUE);
            indicator_line(i);
            /*
               May be:
               indicator_O_o(i) 
               indicator_line(i)
               indicator_arrow(i);

               or everything else ... 
             */
        }
        printf("\n");
    }
    return 1;
}
