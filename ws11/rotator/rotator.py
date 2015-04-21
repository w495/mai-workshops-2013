#!/usr/bin/python
# -*- coding: utf-8

'''
    Выполняет операции поворота для строки.
    Операция поворота определяется начальным
    и конечным символом подстроки, которую нужно повернуть циклически вправо.
    и числом поворотов, которые необходимо произвести.

    Программа принимает на вход исходную строку,
    количество операции, и потом перечисляются сами операции поворота,
    как описано выше.

    Ввод:
        <строка>
        <число_итераций = (n)>
        <начало_1> <конец_1> <число_поворотов_1>
        <начало_2> <конец_2> <число_поворотов_2>

        <начало_n> <конец_n> <число_поворотов_n>

    Примеры:
        Ввод:
            abcdeh
            1
            1 3 1
        Вывод:
            cabdeh

        Ввод:
            abcdeh
            2
            1 2 1
            2 3 1
        Вывод:
            bcadeh

'''

import sys

def main():
    input_generator = get_input_generator(sys.stdin)
    string = next(input_generator, '')
    iter_numbers = next_int(input_generator, 0)
    for iteration in xrange(iter_numbers):
        left_limit = next_int(input_generator, 1)
        right_limit = next_int(input_generator, 1)
        rotation_numbers = next_int(input_generator, 0)
        string = rotate_center(
            string,
            left_limit,
            right_limit,
            rotation_numbers
        )
    sys.stdout.write("%s\n"%string)

def rotate_center(string, left_limit, right_limit, rotation_numbers):
    left = string[:left_limit - 1]
    center = string[left_limit - 1:right_limit]
    right = string[right_limit:]
    center = rotate_string(right_limit - left_limit + 1, center, rotation_numbers)
    return left + center + right

def rotate_string(string_len, string, rotation_numbers):
    rotation_numbers = rotation_numbers % string_len
    return string[-rotation_numbers:] + string[:-rotation_numbers]

def next_int(input_generator, default = 0):
    return toint(next(input_generator, 0))

def toint(a, default = None):
    if(None == a):
        return default
    if isinstance(a, int):
        return a
    if isinstance(a, str) or isinstance(a, unicode):
        if(not check_isdigit(a)):
            return default
    try:
        return int(a)
    except:
        return default
    return default

def check_isdigit(s):
    if len(s) and s[0] in ('-', '+'):
        return s[1:].isdigit()
    return s.isdigit()

def get_input_generator(stream):
    for line in stream:
        for token in line.split():
            yield token

if __name__ == '__main__':
    main()
