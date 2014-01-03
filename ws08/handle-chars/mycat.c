
/*
 * Подключаем заголовочный файл стандартного ввода-вывода 
 * (STanDart Input-Output) для использования getchar, putchar, scanf, printf.
 */
#include<stdio.h>

int main(int argc, char *argv[], char *env[]) {
    char symbol;

    symbol = getchar();
    while (EOF != symbol) {
        putchar(symbol);
        symbol = getchar();
    }
    return 0;
}
