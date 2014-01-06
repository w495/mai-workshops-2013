
/**
 * @section ЗАДАЧА
 *
 *      Составить программу на Си, которая печатает таблицу 
 *      значений элементарной функции, вычисленной двумя способами: 
 *      по формуле Тейлора и с помощью встроенных функций. 
 *      В качестве аргументов таблицы взять точки разбиения отрезка [a, b]
 *      на n равных частей (n + 1 точка, включая концы отрезка), 
 *      находящихся в рекомендованной области хорошей точности формулы Тейлора. 
 *      Вычисления по формуле Тейлора проводить по экономной схеме 
 *      с точностью ε × k, где ε — машинное эпсилон аппаратно реализованного 
 *      вещественного типа для данной ЭВМ, а 
 *      k — экспериментально подбираемый коэффициент, 
 *      обеспечивающий приемлемую сходимость. 
 *      Число итераций должно ограничиваться сверху числом порядка 100. 
 * 
 *      Программа должна сама определять машинное ε 
 *      и обеспечивать корректные размеры генерируемой таблицы.
 * 
 * @section ОПИСАНИЕ
 * 
 *      Программа со стандартного входного потока-файла (stdin) 
 *      считывает число интервалов, на которые требуется разделить отрезок.
 *      В стандартный выходной поток-файл (stdout) печатается количество шагов,
 *      смещение по `x`, величина машинного эпсилона, ширина дробной части 
 *      машинного эпсилона, и таблица значений функций как указано в задании.
 *      
 *          $> gcc -Wall -pedantic -std=c89  -lm  cp3example.c 
 *          $> ./a.out 
 *          10
 *          steps    = 10
 *          Δx       = 0.0500000
 *          ε        = 0.0000001
 *          ε width  = 7
 *          --------------------------------------------------------
 *          | # |            x |       target |       taylor |   n |
 *          --------------------------------------------------------
 *          | 0 |    0.1000000 |   -3.4567902 |   -3.4567802 |   5 |
 *          | 1 |    0.1500000 |   -3.7370241 |   -3.7370210 |   7 |
 *          | 2 |    0.2000000 |   -4.0624995 |   -4.0624919 |   8 |
 *          | 3 |    0.2500000 |   -4.4444447 |   -4.4444399 |  10 |
 *          | 4 |    0.3000000 |   -4.8979597 |   -4.8979554 |  12 |
 *          | 5 |    0.3500000 |   -5.4437876 |   -5.4437761 |  13 |
 *          | 6 |    0.4000000 |   -6.1111112 |   -6.1111064 |  16 |
 *          | 7 |    0.4500000 |   -6.9421496 |   -6.9421387 |  18 |
 *          | 8 |    0.5000001 |   -8.0000019 |   -7.9999938 |  22 |
 *          | 9 |    0.5500001 |   -9.3827181 |   -9.3827076 |  25 |
 *          |10 |    0.6000001 |  -11.2500038 |  -11.2499924 |  30 |
 *          --------------------------------------------------------
 *          $> 
 * 
 *  @authors    Никитин Илья Константинович (преп. каф. 806 МАИ) <w@w-495.ru>
 *  @version    2.1 
 *  @date       2014.01.05 01:59:35
 */

#include <stdio.h>

/*
 * Подключаем заголовочный файл libm для использования функции `log10` 
 * и `ceil`. Но компилировать в этом случае придется с ключом -lm
 *      $> gcc -Wall -pedantic -std=c89 -lm ./programm.c
 */
#include <math.h>

/**
 * @typedef Тип данных для прохождения по отрезку.
 */
typedef long step_t;


/**
 * @typedef Тип данных для итераций по Тейлору.
 */
typedef long iter_t;


/**
 * @typedef Тип данных работы с функциями на отрезке.
 *          Удобно менять с `double` на `float`, 
 *          и смотреть как меняются результаты.
 *          Например, становится легко видеть, 
 *          что для `double` и для  `float` машинный эпсилон разный!
 *          Менять придется только здесь, не трогая остальной программы.
 */
typedef double real_t;


/* *************************************************************************
 * 
 *                      ОСНОВНЫЕ КОНСТАНТЫ И ФУНКЦИИ
 * 
 * *************************************************************************/

/**
 * Начальная точка.
 */
const real_t START_X = 0.1;

/**
 * Конечная точка.
 */
const real_t STOP_X = 0.6;

/**
 * Количество итераций по Тейлору.
 */
const iter_t ITER_LIMIT = 100;

/**
 * Коэффициент сходимости. Подбирался экспериментально.
 */
const real_t COEF = 100.0;


/**
 * @fn Возвращает значение целевой функции в точке `x`.
 */
real_t target_fuction(real_t x);

/**
 * @fn Возвращает значения n-го члена ряда Тейлора в точке `x`.
 */
real_t taylor_fuction(real_t x, iter_t n);

/**
 * @fn Возвращает модуль числа `x`.
 */
real_t rabs(real_t x);

/**
 * @fn Возвращает модуль `n`-ную степень числа `x`.
 */
real_t rpow(real_t x, iter_t n);


/**
 * @fn Вычисляет и возвращает машинное эпсилон.
 */
real_t epsylone();


/**
 * @fn  Приводит число  к 64-битам, 
 *      на случай 80-битового вещественного регистра.
 *      Требуется для правильного вычисления epsylone().
 *      См комментарий на http://k806.ru/infocourse/task3/
 */
real_t findent(real_t x);


/* *************************************************************************
 * 
 *                      КОНСТАНТЫ И ФУНКЦИИ ПЕЧАТИ
 * 
 * *************************************************************************/


/**
 * Формат ввода-вывода данных прохождения по отрезку (шагов).
 */
#define FORMAT_STEP "ld"

/**
 * Формат ввода-вывода данных для итераций по Тейлору.
 */
#define FORMAT_ITER "ld"

/**
 * Формат ввода-вывода значений функции в точке и самой точки.
 * Вместо `f` можно было бы использовать `g` или `lf` как в примерах.
 * Но в `lf` не поддерживается в стандарте c89. 
 * `g` в данном случае может быть более информативным.
 * 
 *      ВЫВОД С `g`:
 * 
 *          $> gcc -Wall -pedantic -std=c89  -lm  cp3example.c 
 *          $> ./a.out 
 *          2
 *          steps    = 2
 *          Δx       = 0.25
 *          ε        = 1.192093e-07
 *          ε width  = 7
 *          --------------------------------------------------------
 *          | # |            x |       target |       taylor |   n |
 *          --------------------------------------------------------
 *          | 0 |          0.1 |     -3.45679 |     -3.45678 |   5 |
 *          | 1 |         0.35 |    -5.443788 |    -5.443782 |  14 |
 *          | 2 |          0.6 |       -11.25 |    -11.24999 |  31 |
 *          --------------------------------------------------------
 * 
 *      ВЫВОД С `f`:
 * 
 *          $> gcc -Wall -pedantic -std=c89  -lm  cp3example.c 
 *          $> ./a.out 
 *          2
 *          steps    = 2
 *          Δx       = 0.2500000
 *          ε        = 0.0000001
 *          ε width  = 7
 *          --------------------------------------------------------
 *          | # |            x |       target |       taylor |   n |
 *          --------------------------------------------------------
 *          | 0 |    0.1000000 |   -3.4567902 |   -3.4567802 |   5 |
 *          | 1 |    0.3500000 |   -5.4437876 |   -5.4437823 |  14 |
 *          | 2 |    0.6000000 |  -11.2500010 |  -11.2499914 |  31 |
 *          --------------------------------------------------------
 */
#define FORMAT_REAL  "f"

/**
 * Размер 
 * Подбирается экспериментально.
 */
const int FORMAT_REAL_LENGTH = 5;

/**
 * Смещение линии таблицы для красивого вывода на экран.
 * Подбирается экспериментально.
 */
const int FORMAT_LINE_OFFSET = 15;


/**
 * @fn Выводит на экран линию для таблицы значений.
 */
void format_print_table_line(int stepwidth, int iterwidth, int epswidth);


/**
 * @fn Выводит на экран заголовок для таблицы значений.
 */
void format_print_table_head(int stepwidth, int iterwidth, int epswidth);

/**
 * @fn Выводит на экран строку для таблицы значений.
 */
void format_print_table_row(
    int stepwidth,
    int iterwidth,
    int epswidth,
    step_t step,
    real_t x,
    real_t target, 
    real_t taylor, 
    iter_t iter
);

int main() {

    /**
     * @var Машинное эпсилон.
     */
    real_t eps = epsylone();

    /**
     * @var Точка в которой мы будем вычислять значения функции на каждом шаге.
     */
    real_t x;

    /**
     * @var Смещение точки на каждом шаге. Δx.
     */
    real_t delta_x;

    /**
     * @var Количество интервалов, на которые мы делим отрезок.
     */
    step_t nsteps;

    /**
     * @var Номер шага по оси `x`.
     */
    step_t step;

    /**  
     * @var Ширина машинного эпсилон, 
     *      т.е. сколько десятичных знаков после запятой занимает эпсилон
     *      при печати. Переменная нужна только для красивого вывода на экран.
     */
    int epswidth;

    /**  
     * @var Ширина номера шага, 
     *      т.е. сколько десятичных цифр занимает номер шага при печати. 
     *      Переменная нужна только для красивого вывода на экран.
     */
    int stepwidth;

    /**  
     * @var Ширина номера итерации по Тейлору, 
     *      т.е. сколько десятичных цифр занимает номер итерации при печати. 
     *      Переменная нужна только для красивого вывода на экран.
     */
    int iterwidth;

    /*
     * Считываем количество шагов.
     */
    scanf("%" FORMAT_STEP, &nsteps);

    /*
     * Вычисляем дельту, смещение точки на каждом шаге.
     */
    delta_x = (STOP_X - START_X) / nsteps;

    /*
     * Вычисляем ширину эпсилон.
     */
    epswidth = ceil(-log10(eps));

    /*
     * Вычисляем ширину номера шага.
     */
    stepwidth = ceil(log10(nsteps) + 1);

    /*
     * Вычисляем ширину номера итерации по тейлору.
     */
    iterwidth = ceil(log10(ITER_LIMIT) + 1);

    /*
     * Выводим интересующие нас величины.
     */
    printf("steps    = %ld\n", nsteps);
    printf("Δx       = %.*" FORMAT_REAL "\n", epswidth, delta_x);
    printf("ε        = %.*" FORMAT_REAL "\n", epswidth, eps);
    printf("ε width  = %d\n", epswidth);

    /*
     * Рисуем шапку таблицы
     */
    format_print_table_line(stepwidth, iterwidth, epswidth);
    format_print_table_head(stepwidth, iterwidth, epswidth);
    format_print_table_line(stepwidth, iterwidth, epswidth);

    x = START_X;
    for (step = 0; step != (nsteps + 1); ++step) {
        iter_t iter = 0;

        /* Значение нулевого члена ряда Тейлора в точке `x`. */
        real_t taylor = taylor_fuction(x, iter);

        /* Значение целевой функции в точке `x`. */
        real_t target = target_fuction(x);

        while ((rabs(target - taylor) >= (eps * COEF)) && iter < ITER_LIMIT) {
            ++iter;
            /* Значение n-го члена ряда Тейлора в точке `x`. */
            taylor += taylor_fuction(x, iter);
        }

        /*
         * Рисуем строку таблицы.
         */
        format_print_table_row(stepwidth, iterwidth, epswidth,
                               step, x, target, taylor, iter);

        /*
         * Увеличиваем `x` на `Δx`.
         */
        x += delta_x;
    }

    /*
     * Рисуем подол таблицы.
     */
    format_print_table_line(stepwidth, iterwidth, epswidth);

    return 0;
}


/* 
 * ОСНОВНЫЕ ФУНКЦИИ
 */


/**
 * @fn Возвращает значение функции в точке `x`.
 */
real_t target_fuction(real_t x) {
    return (2 * x - 3) / ((x - 1) * (x - 1));
}


/**
 * @fn Возвращает значения n-го члена ряда Тейлора в точке `x`.
 */
real_t taylor_fuction(real_t x, iter_t n) {
    return -(n + 3) * rpow(x, n);
}

/**
 * @fn Возвращает модуль числа `x`.
 */
real_t rabs(real_t x) {
    if (x < 0)
        return -x;
    return x;
}

/**
 * @fn Возвращает модуль `n`-ную степень числа `x`.
 */
real_t rpow(real_t x, iter_t n) {
    iter_t i;
    real_t res = 1;

    for (i = 0; i != n; ++i) {
        res *= x;
    }
    return res;
}


/**
 * @fn  Приведения к 64-битам, на случай 80-битового вещественного регистра.
 *      См комментарий на http://k806.ru/infocourse/task3/
 */
real_t findent(real_t x) {
    return x;
}

/**
 * @fn Вычисляет и возвращает машинное эпсилон.
 */
real_t epsylone() {
    real_t eps = 1.0;

    while (findent(eps / 2 + 1) > 1)
        eps = eps / 2;
    return eps;
}

/* 
 * ФУНКЦИИ ПЕЧАТИ 
 */

/**
 * @fn  Выводит на экран линию для таблицы значений.
 *      Чтобы понять, что происходит, читайте документацию к printf.
 */
void format_print_table_line(int stepwidth, int iterwidth, int epswidth) {
    int epslength = epswidth + FORMAT_REAL_LENGTH;
    int size = stepwidth + 3 * epslength + iterwidth + FORMAT_LINE_OFFSET;
    int i;

    for (i = 0; i != size; ++i) {
        printf("-");
    }
    printf("\n");
}

/**
 * @fn  Выводит на экран заголовок для таблицы значений.
 *      Чтобы понять, что происходит, читайте документацию к printf.
 */
void format_print_table_head(int stepwidth, int iterwidth, int epswidth) {
    int epslength = epswidth + FORMAT_REAL_LENGTH;

    printf("|%*s |", stepwidth, "#");
    printf(" %*s |", epslength, "x");
    printf(" %*s |", epslength, "target");
    printf(" %*s |", epslength, "taylor");
    printf(" %*s |\n", iterwidth, "n");
}

/**
 * @fn  Выводит на экран строку для таблицы значений.
 *      Чтобы понять, что происходит, читайте документацию к printf.
 */
void format_print_table_row(
    int stepwidth,
    int iterwidth,
    int epswidth,
    step_t step,
    real_t x,
    real_t target, 
    real_t taylor, 
    iter_t iter
) {
    int epslength = epswidth + FORMAT_REAL_LENGTH;

    printf("|%*" FORMAT_STEP " |", stepwidth, step);
    printf(" %*.*" FORMAT_REAL " |", epslength, epswidth, x);
    printf(" %*.*" FORMAT_REAL " |", epslength, epswidth, target);
    printf(" %*.*" FORMAT_REAL " |", epslength, epswidth, taylor);
    printf(" %*" FORMAT_ITER " |\n", iterwidth, iter);
}
