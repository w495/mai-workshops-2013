/**
 * @section ЗАДАЧА
 * 
 *      Составить программу на языке Си, производящую обработку
 *      квадратной матрицы порядка NxN (0 <= N <= 512), из целых чисел,
 *      вводимой из стандартного входного текстового файла (stdin).
 *      Результат программы выводится на стандартный поток вывода (stdout).
 *
 *      В данном варианте требуется выполнить циклический сдвиг 
 *      элементов матрицы в строчном представлении на S элементов.
 *      S тоже считывает из стандартного входного текстового файла (stdin).
 * 
 *      Формат ввода имеет вид:
 *
 *          {N} {S}
 *          {x_11}  {x_21}  ... {x_1N} 
 *          {x_12}  {x_22}  ... {x_2N}
 *                          ...
 *          {x_N1}  {x_N2}  ... {x_NN}
 *
 *          Где, N --- размер матрицы, а S --- величина сдвига.
 *
 *          ПРИМЕР:
 * 
 *              $> gcc -Wall -pedantic -std=c89 ./programm.c 
 *              $> ./a.out 
 *              3 1
 *              1 2 3
 *              4 5 6
 *              7 8 9
 *
 *              9 1 2 
 *              3 4 5 
 *              6 7 8 
 *              $> ./a.out 
 *              3 2 
 *              1 2 3
 *              4 5 6
 *              7 8 9
 *
 *              8 9 1 
 *              2 3 4 
 *              5 6 7 
 *              $> 
 *
 * 
 *  @authors    Ганиев Дмитрий Юрьевич (студент 8O-101Б МАИ, 2013)
 *              Никитин Илья Константинович (преп. каф. 806 МАИ) <w@w-495.ru>
 * 
 *  @version    1.1
 */ 

/*
 * Подключаем заголовочный файл стандартного ввода-вывода 
 * (STanDart Input-Output) для использования getchar, putchar, scanf, printf.
 */
#include <stdio.h>

/**
 * @const Максимальный размер матрицы.
 */ 
#define MAX_MATRIX_SIZE 512

int main() {

    /**
     * @var Рабочая матрица.
     */ 
    int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

    /**
     * @var Размер матрицы.
     *      В качестве типа можно использовать int.
     *      Но `size` у нас по заданию ограничен и достаточно мал.
     *      Потому можно ограничится `short`.
     */ 
    short size;

    /**
     * @vars Переменные для индексов строк и столбцов.
     */ 
    short i, j;

    /**
     * @var Переменная для хранения переноса числа из конца матрицы в начало.
     */ 
    int carry;
    
    /**
     * @var Размер сдвига.
     */ 
    short shift; 

    /**
     * @var Шаг сдвига.
     */ 
    short step;

    /*
     * Считываем размер матрицы и величину сдвига.
     */ 
    scanf("%hd %hd", &size, &shift);
    
    /*
     * Защита от дурака.
     */ 
    if (!((0 <= size) &&  (size <= MAX_MATRIX_SIZE))) {
        printf("wrong input\n");
        return 1;
    }

    /*
     * Нормируем величину сдвига.
     */ 
    shift = shift % (size * size);

    /*
     * Cчитываем саму матрицу.
     */ 
    for(i = 0; i != size; ++i)
        for(j = 0; j != size; ++j)
            scanf("%d", &matrix[i][j]);

    /*
     * Сдвигаем матрицу на величину `shift`,
     * по одному элементу на шаг цикла.
     */ 
    step = 1;
    while (step <= shift) {
        /*
         * Циклически сдвигаем матрицу на 1 элемент.
         * При этом, учитываем, что последний элемент 
         * матрицы становится первым.
         */ 
        carry = matrix[size - 1][size - 1];
        for (i = size - 1; i >= 0; --i) {
            for (j = size - 1; j >= 0; --j) {
                if (j > 0) {
                    matrix[i][j] = matrix[i][j - 1];
                }
                else if(i > 0) {
                    matrix[i][j] = matrix[i - 1][size - 1];
                }
                else {
                    matrix[i][j] = carry;
                }
            }
        }
        ++step;
    }

    printf("\n");

    /*
     * Вывод матрицы на печать.
     */ 
    for (i = 0; i != size; ++i) {
        for (j = 0; j != size; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}