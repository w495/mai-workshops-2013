#include<stdio.h>

#include"indicator.h"

#define CASES 5

int _indicator(int i, char c0, char c1, char c2, char c3, char c4) {
    switch (i % CASES) {
        case 0:
            printf("\b%c", c0);
            break;
        case 1:
            printf("\b%c", c1);
            break;
        case 2:
            printf("\b%c", c2);
            break;
        case 3:
            printf("\b%c", c3);
            break;
        default:
            /*CASES - 1 */
            printf("\b%c", c4);
            break;
    }
    return i;
}

int _mindicator(int i, char c0, char c1, char c2, char c3, char c4,
                char track) {
    switch (i % CASES) {
        case 0:
            printf("\b%c%c", track, c0);
            break;
        case 1:
            printf("\b%c", c1);
            break;
        case 2:
            printf("\b%c", c2);
            break;
        case 3:
            printf("\b%c", c3);
            break;
        default:
            /*CASES - 1 */
            printf("\b%c", c4);
            break;
    }
    return i;
}

int _findicator(FILE * stream, int i, char c0, char c1, char c2, char c3,
                char c4) {
    switch (i % CASES) {
        case 0:
            fprintf(stream, "\b%c", c0);
            break;
        case 1:
            fprintf(stream, "\b%c", c1);
            break;
        case 2:
            fprintf(stream, "\b%c", c2);
            break;
        case 3:
            fprintf(stream, "\b%c", c3);
            break;
        default:
            /*CASES - 1 */
            fprintf(stream, "\b%c", c4);
            break;
    }
    return i;
}

int _fmindicator(FILE * stream, int i, char c0, char c1, char c2, char c3,
                 char c4, char track) {
    switch (i % CASES) {
        case 0:
            fprintf(stream, "\b%c%c", track, c0);
            break;
        case 1:
            fprintf(stream, "\b%c", c1);
            break;
        case 2:
            fprintf(stream, "\b%c", c2);
            break;
        case 3:
            fprintf(stream, "\b%c", c3);
            break;
        default:
            /*CASES - 1 */
            fprintf(stream, "\b%c", c4);
            break;
    }
    return i;
}
