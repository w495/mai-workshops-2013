#!/usr/bin/env python
# -*- coding: utf8 -*-

##
##  Простая программа перевода двоичных строк входного потока,
##  в байты выходного потока.
##  На вход подаются строки, например
##      01001000
##      01100101
##      01101100
##      01101100
##      01101111
##      00001010
##  В результате работы программы они будут переведены в строку `Hello`
##

import sys
import string

if __name__ == '__main__':
    while True:
        # Читаем построчно из входного потока.
        line = sys.stdin.readline()
        # Если читать больше нечего (конец файла --- `EOF`), 
        # то прерываем цикл.
        if(not line):
            break;
        # Переводим считанную строку из двоичной системы счисления.
        # В итоге получаем некоторое число --- номер символа.
        number = string.atoi(line, 2)
        # Получаем символ ASCII по его номеру.
        char = chr(number)
        # Записываем символ в выходной поток
        sys.stdout.write(char)