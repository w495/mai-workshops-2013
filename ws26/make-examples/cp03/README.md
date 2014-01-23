
# Что это

Пример курсовой работы по Основам информатики. 
Распространяется как пример проекта с использованием `Makefile`.

Печатает таблицу значений элементарной функции, 
вычисленной двумя способами: по формуле Тейлора и с помощью встроенных функций. 
В качестве аргументов таблицы берутся точки разбиения отрезка `[a, b]`
на `n` равных частей (`n + 1` точка, включая концы отрезка), 
находящихся в рекомендованной области хорошей точности формулы Тейлора. 
Вычисления по формуле Тейлора проводятся по экономной схеме 
с точностью `ε × k`, где `ε` — машинное эпсилон аппаратно реализованного 
вещественного типа для данной ЭВМ, а `k` — экспериментально 
подобранный коэффициент, обеспечивающий приемлемую сходимость. 
Число итераций ограничивается сверху числом порядка `100`.

Программа сама определяет машинное `ε` и обеспечивает 
корректные размеры генерируемой таблицы.

Проект разбит на `4` логических части:
* описание типов данных, и работы с ними (вычисление длины);
* описание целевая и численной функций и вычисление машинного эпсилон;
* форматированный вывод таблицы;
* модуль управления — бизнес-логика проекта.

Проект разбиты на `8` файлов (по 2 на каждую логическую часть):
* `4` заголовочных файла;
* `4` файла с исходным кодом.

К проекту прилагается файл с правилами сборки `Makefile` 
и файл с описанием зависимостей `.depend`.

## Структура проекта
    .
    |-- Makefile            # Файл с описанием сборки.
    |-- .depend             # Описание зависимостей для сборки.
    |-- README.md           # Человеческое описание проекта.
    |-- includes            # Папка с заголовочными файлами (объявление).
    |   |-- libformat.h     #   Форматированный вывод.
    |   |-- libfunc.h       #   Функции: целевая и численная, машинный эпсилон.
    |   |-- libtypes.h      #   Типы данных для работы с функциями.
    |   `-- main.h          #   Настройки
    `-- src                 # Папка с файлами исходного кода (реализация).
        |-- libformat.c     #   Форматированный вывод.
        |-- libfunc.c       #   Функции: целевая и численная, машинный эпсилон.
        |-- libtypes.c      #   Типы данных для работы с функциями.
        `-- main.c          #   Основная логика программы.


## Что нужно для сборки

* `bash` или любая иная совместима оболочка.
* `make` >= v3.0;
* `sed`;
* `gcc`;
* `libm` (обычно, она часть `glibc`).

Могут так же потребоваться:

* `tar`;
* `bzip2`;
* `less`.

## Сборка

Если все необходимые компоненты есть, то достаточно набрать только `make`.

    $> make
    #       Создаем директорию ./obj если ее нет.
    mkdir -p obj
    # 
    #       Собираем объектные файлы из исходных файлов с кодом.
    #               Подключаем директорию с .h через опцию -I.
    #               Если компиляция не свершилась, шумно сообщаем об этом.
    # 
    gcc -c -Wall -pedantic -std=c89 -I./includes src/libtypes.c -o obj/libtypes.o \
    || (    echo -e "\n\nMAY BE PROBLEMS WITH '.depend'."  &&       \
            echo -e "CHECK IT OR FIX IT WITH 'make depend'.\n\n" && \
            exit 1;);
    # 
    #       Собираем объектные файлы из исходных файлов с кодом.
    #               Подключаем директорию с .h через опцию -I.
    #               Если компиляция не свершилась, шумно сообщаем об этом.
    # 
    gcc -c -Wall -pedantic -std=c89 -I./includes src/libfunc.c -o obj/libfunc.o \
    || (    echo -e "\n\nMAY BE PROBLEMS WITH '.depend'."  &&       \
            echo -e "CHECK IT OR FIX IT WITH 'make depend'.\n\n" && \
            exit 1;);
    # 
    #       Собираем объектные файлы из исходных файлов с кодом.
    #               Подключаем директорию с .h через опцию -I.
    #               Если компиляция не свершилась, шумно сообщаем об этом.
    # 
    gcc -c -Wall -pedantic -std=c89 -I./includes src/libformat.c -o obj/libformat.o \
    || (    echo -e "\n\nMAY BE PROBLEMS WITH '.depend'."  &&       \
            echo -e "CHECK IT OR FIX IT WITH 'make depend'.\n\n" && \
            exit 1;);
    # 
    #       Собираем объектные файлы из исходных файлов с кодом.
    #               Подключаем директорию с .h через опцию -I.
    #               Если компиляция не свершилась, шумно сообщаем об этом.
    # 
    gcc -c -Wall -pedantic -std=c89 -I./includes src/main.c -o obj/main.o \
    || (    echo -e "\n\nMAY BE PROBLEMS WITH '.depend'."  &&       \
            echo -e "CHECK IT OR FIX IT WITH 'make depend'.\n\n" && \
            exit 1;);
    # 
    #       Собираем исполняемый файл из объектных.
    # 
    gcc -lm obj/libtypes.o obj/libfunc.o obj/libformat.o obj/main.o -o cp3
    $> 


## Ввод-вывод
 
Программа со стандартного входного потока-файла (stdin) 
считывает число интервалов, на которые требуется разделить отрезок.
На стандартный выходной поток-файл (stdout) печатается таблица.

    $> make -s
    $> ./cp3 
    10
    --------------------------------------------------------
    | # |            x |       target |       taylor |   n |
    --------------------------------------------------------
    | 0 |    0.1000000 |   -3.4567902 |   -3.4567802 |   5 |
    | 1 |    0.1500000 |   -3.7370241 |   -3.7370210 |   7 |
    | 2 |    0.2000000 |   -4.0624995 |   -4.0624919 |   8 |
    | 3 |    0.2500000 |   -4.4444447 |   -4.4444399 |  10 |
    | 4 |    0.3000000 |   -4.8979597 |   -4.8979554 |  12 |
    | 5 |    0.3500000 |   -5.4437876 |   -5.4437761 |  13 |
    | 6 |    0.4000000 |   -6.1111112 |   -6.1111064 |  16 |
    | 7 |    0.4500000 |   -6.9421496 |   -6.9421387 |  18 |
    | 8 |    0.5000001 |   -8.0000019 |   -7.9999938 |  22 |
    | 9 |    0.5500001 |   -9.3827181 |   -9.3827076 |  25 |
    |10 |    0.6000001 |  -11.2500038 |  -11.2499924 |  30 |
    --------------------------------------------------------
    $> 
 
# Авторы

Илья w-495 Никитин  (преп. каф. 806 МАИ) <w@w-495.ru>

Последнее изменение: `2014.01.05 01:59:35`

 