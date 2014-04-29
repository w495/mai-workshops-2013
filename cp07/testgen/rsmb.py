# -*- coding: utf8 -*-

'''
    Простой генератор случайных разреженных матриц.
    Случайными могут быть, как размер матрицы, так и ее значение.
    С помощью аргументов командной строки можно управлять размером матрицы,
    формой вывода и вероятностью появления не нулевых элементов.
    Для правильного использование смотрите описание аргументов
    и справку (./rsmb.py --help ).

    @author     Илья w-495 Никитин <w@w-495.ru>, ПМФ МАИ
    @date       2014.04.29 19:52:15
'''

HELP_DESCRIPTION="""\033[1m
Simple random sparse matrix builder.    \033[0m

It prints to `stdout` matrix with format
\033[33m
    <width> <height>
    <cell_11>   ... <cell_1n>
        ...     ...     ...
    <cell_k1>   ... <cell_kn>
\033[0m
You can tune the matrix generation or even format of matrix.
See examples for it.

"""

HELP_EXAMPLES="""\033[1m
Examples:   \033[0m

    1) Generate a random sparse matrix 10x10 with not-null elements in [1..9]
    \033[33m
        $> %(prog)s -x 10 -y 10 -mv 1 -Mv 9
        10 10
        0 0 0 2 0 0 0 0 0 0
        7 0 0 0 0 0 4 0 3 0
        5 0 0 6 0 0 0 0 0 0
        5 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 5 0
        2 1 5 0 0 0 0 0 0 0
        0 0 3 0 0 4 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 6 0 0 0 1 0 0 0
    \033[0m

    2) Generate a random sparse matrix with a random width (in range [1..10])
    and height (in range [5..15])
    \033[33m
        $> %(prog)s -mx 1 -my 5 -Mx 10 -My 15 -mv 1 -Mv 9
        8 10
        0 0 0 0 0 0 0 6 0 0
        0 1 0 0 0 0 5 0 0 0
        3 0 0 0 0 0 7 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 4 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 7 0 0 0 0 4
        0 0 0 0 0 0 0 0 0 3
    \033[0m

    3) Generate a square random sparse matrix with a random width
    and height both in range [1..10]
    \033[33m
        $> %(prog)s  -ms 1 -Ms 10 -sq -mv 1 -Mv 9
        5 5
        0 0 0 0 0
        3 0 6 0 1
        3 1 0 0 0
        0 0 0 0 0
        0 0 0 0 0
    \033[0m

    4) Generate a random sparse matrix with random a width and height both
    in range [1..10] and a probability of not-null cells, that equals 0.5
    \033[33m
        $> %(prog)s -ms 1 -Ms 10 -mv 1 -Mv 9 -p 0.5
        9 8
        0 1 8 1 3 1 7 7
        4 0 0 3 0 0 0 6
        6 2 3 0 0 6 0 0
        0 5 0 0 0 4 0 5
        0 0 3 8 5 0 2 0
        2 7 8 0 7 6 5 0
        5 8 3 7 0 7 0 0
        4 0 0 0 4 1 0 7
        7 0 0 2 3 3 4 0
    \033[0m

    5) Generate a random sparse matrix and print it in one line.
    Leading `8` and `2` --- is a dimention of the matrix.
    \033[33m
        $> %(prog)s -ms 1 -Ms 10 -mv 1 -Mv 9 -l1
        8 2 0 0 0 0 0 5 0 0 0 0 0 0 0 0 0 0
    \033[0m

    6) Generate a random sparse matrix and print it without size.
    \033[33m
        $> %(prog)s -ms 1 -Ms 10 -mv 1 -Mv 9  -ns
        0 0 0 0 0 0 0 0 0
        0 3 0 0 0 0 0 0 4
        0 0 0 8 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 7 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
    \033[0m
"""

##
##  Трюк для правильной записи в stdout через file.write
##  В использовании не обязателен.
##
import signal
signal.signal(signal.SIGPIPE, signal.SIG_DFL)

##
## Для записи в stdout
##
import sys

##
## Для генерации случайных чисел
##
import random

##
## Для работы с аргументами командной строки
##
import argparse

##
##  Максимальная величина для целого числа
##  sys.maxint будет разным на разных машинах
##
LIMIT_MAX_INT = sys.maxint

##
##  Минимальная величина для целого числа
##  sys.maxint будет разным на разных машинах
##
LIMIT_MIN_INT = - sys.maxint - 1

##
## Минимальная ширина матрицы по-умолчанию
##
DEFAULT_MIN_WIDTH = 1

##
## Максимальная ширина матрицы по-умолчанию
##
DEFAULT_MAX_WIDTH = 1024

##
## Минимальная высота матрицы по-умолчанию
##
DEFAULT_MIN_HEIGHT = 1

##
## Максимальная высота матрицы по-умолчанию
##
DEFAULT_MAX_HEIGHT = 1024

##
## Вероятность ненулевого элемента
##
DEFAULT_NOTNULL_PROB = 0.1

##
## Минимальная величина не нулевого элемента
##
DEFAULT_MINVALUE    = LIMIT_MIN_INT

##
## Максимальная величина не нулевого элемента
##
DEFAULT_MAXVALUE    = LIMIT_MAX_INT

##
## На всякий случай, будем использовать
## в качестве выходного потока отдельную переменную
##
iostream = sys.stdout

def main():
    config = configure()
    build_matrix(config)

def build_matrix(config):
    '''
        Строит случайную матрицу на основе конфигурации.

        @param config object{
            width    =  <WIDTH>     :: int,   # ширина матрицы
            height   =  <HEIGHT>    :: int,   # высота матрицы
            prob     =  <PROB>      :: [0;1], # вероятность ненулевого элемента
            max      =  <MAX>       :: int,   # максимальный ненулевой элемент
            min      =  <MIN>       :: int,   # минимальный ненулевой элемент
            no_size  =  <True|False>,         # флаг печати размера
            one_line =  <True|False>,         # флаг печати в одну строку
        }

    '''

    ##
    ## Порог для предотвращения деления
    ## на ноль при обработке вероятности.
    ##
    ZERODISION_THRESHOLD = 0.0000001

    if(not config.no_size):
        iostream.write("%s %s "%(config.width, config.height))

    for i in xrange(config.width):
        for j in xrange(config.height):
            # На основе вероятности из конфигурации меняем диапазон,
            # по которому вычисляем вероятность выпадения единицы.
            # Вероятность в конфигурации и примерная есть вероятность
            # выпадения единицы в нашем диапазоне.
            rand0 = int(random.uniform(
                ZERODISION_THRESHOLD,
                1.0/(config.prob + ZERODISION_THRESHOLD))
            )
            res = 0
            if(rand0 == 1):
                # Если выпала не единица, то считаем,
                # что в матрице на этом месте будет не нуль.
                res = int(random.uniform(config.min_value, config.max_value))
            iostream.write("%s "%(res))

        if(not config.one_line):
            iostream.write("\n")

    if(config.one_line):
        iostream.write("\n")


def configure():
    '''
        Возвращает конфигурацию для функции build_matrix.
        Конфигурация берется из аргументов командной строки.
    '''

    # Создадим парсер аргуметов командной строки.
    # Для аналогичной задачи можно использовать getopt.
    # Но в данном случае, мы решили использовать argparse.
    parser = argparse.ArgumentParser(
        description     =   HELP_DESCRIPTION,
        epilog          =   HELP_EXAMPLES,
        formatter_class =   argparse.RawDescriptionHelpFormatter,
    )

    # Далее опишем какие могут быть аргуметы командной строки.

    # Ширина матрицы. Если хотим задать точную.
    parser.add_argument(
        '-x',   '--width',
        type    =   check_size,
        default =   None,
        help    =   'matrix width '
        '(default: it is random between  `min-width` and `max-width`).'
    )

    # Высота матрицы. Если хотим задать точную.
    parser.add_argument(
        '-y',   '--height',
        type    =   check_size,
        default =   None,
        help    =   'matrix height  (default: it is random)'
        '(default: it is random between `min-height` and `max-height`).'
    )

    # Вероятность появления не нулевых элементов.
    parser.add_argument(
        '-p',   '--prob',
        type    =   check_probability,
        default =   DEFAULT_NOTNULL_PROB,
        help    =   'probability of not-null cell  (default: %(default)s).'
    )

    # Минимальный размер матрицы (и высота и ширина)
    # Используется для вычисления случайных размеров матрицы.
    parser.add_argument(
        '-ms',  '--min-size',
        type    =   check_size,
        default =   None,
        help    =   'minimal size of matrix (both width and height) '
        'it overwrites `min-height` and `min-width`.'
    )

    # Максимальный размер матрицы (и высота и ширина)
    # Используется для вычисления случайных размеров матрицы.
    parser.add_argument(
        '-Ms',  '--max-size',
        type    =   check_size,
        default =   None,
        help    =   'maximal size of matrix (both width and height)'
        'it overwrites `max-height` and `max-width`.'
    )

    # Минимальная ширина.
    parser.add_argument(
        '-mx',  '--min-width',
        type    =   check_size,
        default =   DEFAULT_MIN_WIDTH,
        help    =   'minimal matrix width (default: it is %(default)s).'
    )

    # Максимальная ширина.
    parser.add_argument(
        '-Mx',  '--max-width',
        type    =   check_size,
        default =   DEFAULT_MAX_WIDTH,
        help    =   'maximal matrix width (default: it is %(default)s).'
    )

    # Минимальная высота.
    parser.add_argument(
        '-my',  '--min-height',
        type    =   check_size,
        default =   DEFAULT_MIN_HEIGHT,
        help    =   'minimal matrix height  (default: it is %(default)s).'
    )

    # Максимальная высота.
    parser.add_argument(
        '-My',  '--max-height',
        type    =   check_size,
        default =   DEFAULT_MAX_HEIGHT,
        help    =   'maximal matrix height  (default: it is %(default)s).'
    )

    # Минимальное значение для ненулевого элемента матрицы.
    # Используется для вычисления случайных ненулевых элементов.
    parser.add_argument(
        '-mv',  '--min-value',
        type    =   int,
        default =   DEFAULT_MINVALUE,
        help    =   'minimal value of not-null cell (default: %(default)s).'
    )

    # Максимальное значение для ненулевого элемента матрицы.
    # Используется для вычисления случайных ненулевых элемен
    parser.add_argument(
        '-Mv',  '--max-value',
        type    =   int,
        default =   DEFAULT_MAXVALUE,
        help    =   'maximal value of not-null cell (default: %(default)s).'
    )

    # Флаг, что не нужно выводить размер матрицы.
    parser.add_argument(
        '-ns',  '--no-size',
        action  =   'store_true',
        help    =   'flag: do not write matrix size before matrix.'
    )

    # Флаг, что нужно выводить всю матрицу в одну стоку.
    parser.add_argument(
        '-l1',  '--one-line',
        action  =   'store_true',
        help    =   'flag: print matrix in one line.'
    )

    # Флаг, что матрица должна быть квадратной.
    parser.add_argument(
        '-sq',  '--square',
        action  =   'store_true',
        help    =   'flag: make square matrix.'
    )

    # Получаем от парсера объект конфигурации.
    config = parser.parse_args()

    # Если задан минимальный размер матрицы,
    # перезаписываем минимальную ширину и высоту.
    if(config.min_size):
        config.min_width  = config.min_size
        config.min_height = config.min_size

    # Если задан максимальный размер матрицы,
    # перезаписываем максимальную ширину и высоту.
    if(config.max_size):
        config.max_width  = config.max_size
        config.max_height = config.max_size

    # Если нет четко заданной ширины, то задаем ее случайным образом,
    # как число из отрезка между минимальной и максимальной высотой.
    if(not config.width):
        config.width = int(random.uniform(config.min_width, config.max_width))

    # Если нет четко заданной высоты, то задаем ее случайным образом.
    if(not config.height):
        config.height = int(random.uniform(config.min_height, config.max_height))

    # Если сказано, что матрица должна быть квадратной,
    # делаем высоту равной ширине.
    if(config.square):
        config.height = config.width

    return config

def check_size(string):
    '''
        Проверяет, является входная строка верным размером.
    '''
    size = int(string)
    if(1 <= size <= LIMIT_MAX_INT):
        return size
    raise argparse.ArgumentTypeError("%s is not a right size" % prob)

def check_probability(string):
    '''
        Проверяет, является входная строка вероятностью,
        и в случае успеха возвращает преобразованное значение.
    '''
    prob = float(string)
    if(0.0 <= prob <= 1.0):
        return prob
    raise argparse.ArgumentTypeError("%s is not a right probability" % prob)

if __name__ == '__main__':
    main()
