/**
 * @section ЗАДАЧА
 * 
 *      Составить программу ввода квадратной матрицы 
 *      и печати в строку всех ее элементов 
 *      в заданном ниже порядке обхода. 
 *
 *          7 13 14 16
 *          6  8 12 15
 *          2  5  9 11
 *          1  3  4 10
 *
 *      Исходные данные программы считываются со стандартного ввода (stdin).
 *      Результат программы выводится на стандартный поток вывода (stdout).
 *      На стандартный поток ошибок (stderr) выводится отладочная печать.
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
 * @typedef Логический тип данных. 
 *          В Си его нет, потому введем его сами, 
 *          чтобы работать не с нулями и единицами,
 *          а c нормальными логическими значениями.
 *          Тут можно было бы использовать `stdbool.h` 
 *          и использовать встроенный тип `bool`.
 *          Но этот тип не поддерживается стандартом c89.
 */
typedef enum {FALSE, TRUE} bool_t;

/**
 * @const Константа включения-отключение отладочной печати.
 */ 
const bool_t DEBUG = TRUE;

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
     */ 
    int size;

    /**
     * @vars Переменные для индексов строк и столбцов.
     */ 
    int i, j;

    /**
     * @var Переменная для обхода матрицы при линеаризации.
     */ 
    int k;

    /**
     * @var Флаг направления движения "наискосок".
     *          Если он четный, то двигаться надо 
     *              вниз по строкам и вправо по столбцам.
     *          Если он нечетный, то двигаться надо
     *              вверх по строкам и влево по столбцам.
     */ 
    int direction = 1; 

    /**
     * @var Флаг изменения строк.
     */ 
    bool_t is_row_changed = TRUE; 

    /**
     * @var Флаг изменения столбцов.
     */ 
    bool_t is_col_changed = TRUE;

    /*
     * Cчитываем размер матрицы.
     */ 
    scanf("%d", &size);

    /*
     * Защита от дурака.
     */ 
    if(!((0 <= size) &&  (size <= MAX_MATRIX_SIZE))){
        printf("wrong input\n");
        return 1;
    }
    
    /*
     * Cчитываем саму матрицу.
     */ 
    for(i = 0; i != size; ++i)
        for(j = 0; j != size; ++j)
            scanf("%d", &matrix[i][j]);

    /*
     * Обход и печать матрицы
     */ 
    i = size - 1; 
    j = 0;
    printf("%d ", matrix[i][j]);

    for(k = 1; k <= size * size - 1; ++k){
        if(
            (TRUE == is_row_changed) 
            && (
                (
                    /* матрица четная */
                    (0 == (size % 2)) 
                    && (0 != i) 
                    && ((0 == j) || ((size - 1) == j))
                ) || (
                    /* матрица нечетная */
                    (0 != (size % 2))
                    && (0 != i) 
                    && ((size - 1) != i) 
                    && ((0 == j) || ((size - 1) == j))
                ) || (
                    (size - 1 == i) 
                    && (0 == j)
                )
            )
        ){
            if(DEBUG){
                /* Отладочная печать */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d\n", 
                    k, i, j, matrix[i][j]
                );
            }
            /*
             * Идем вверх по стокам.
             */ 
            --i;
            is_row_changed = FALSE;
            is_col_changed = TRUE;
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d (up)\n", 
                    k, i, j, matrix[i][j]
                );
            }
        }
        else if(
            (TRUE == is_col_changed)
            && (
                (
                    (0 == (size % 2)) 
                    && ((size - 1) != j) 
                    && (0 != j) 
                    && ((0 == i) || ((size - 1) == i))
                ) || (
                    (0 != (size % 2))  
                    && ((0 == i) || ((size - 1) == i))
                )
            )
        ){
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d\n", 
                    k, i, j, matrix[i][j]
                );
            }
            /*
             * Идем вправо по столбцам.
             */ 
            ++j;
            is_row_changed = TRUE;
            is_col_changed = FALSE;
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d (right)\n", 
                    k, i, j, matrix[i][j]
                );
            }
        }
        else if(0 != (direction % 2)) {
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d\n", 
                    k, i, j, matrix[i][j]
                );
            }
            /*
             * Идем вниз по строкам и вправо по столбцам.
             */ 
            ++i;
            ++j;
            if(((size - 1) == i) || ((size - 1) == j)){
                ++direction;
            }
            is_row_changed = TRUE;
            is_col_changed = TRUE;
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d (down, right)\n", 
                    k, i, j, matrix[i][j]
                );
            }
        }
        else {
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d\n", 
                    k, i, j, matrix[i][j]
                );
            }
            /*
             * Идем вверх по строкам и влево по столбцам.
             */ 
            --i;
            --j;
            if ((0 == i) || (0 == j)){
                ++direction;
            }
            is_col_changed = TRUE;
            is_row_changed = TRUE;
            if(DEBUG){
                /* Отладочная печать  */ 
                fprintf(
                    stderr, 
                    "%d, matrix[%d][%d] = %d (top, left)\n", 
                    k, i, j, matrix[i][j]
                );
            }
        }
        printf("%d ", matrix[i][j]);
    }
     printf("\n");
    return 0;
}
