#include <stdio.h>
#include <math.h>
#include <float.h>

/**
 * @typedef Тип данных работы с функциями на отрезке.
 *          Удобно менять с `double` на `float`, 
 *          и смотреть как меняются результаты.
 *          Например, становится легко видеть, 
 *          что для `double` и для  `float` машинный эпсилон разный!
 *          Менять придется только здесь, не трогая остальной программы.
 */
typedef double real_t;

/**
 * @typedef Тип данных передачи функции в качестве параметра. 
 */
typedef real_t (*fun_t) (real_t);

/**
 * @const   Машинное эпсилон.
 *          Можно было бы вычислять машинное эпсилон самим 
 *          как мы это делали в третьем задании КП.
 *          Но можно воспользоваться предопределенной константой из `float.h`.
 *          Для разных типов числе с плавающей точкой 
 *          используются разные константы.
 *              FLT_EPSILON, 
 *              DBL_EPSILON, 
 *              LDBL_EPSILON.
 *          На различных машинах они могут быть различны. 
 *          Потому нельзя закладываться на конкретные значения.
 */ 
const real_t REAL_EPSILON = DBL_EPSILON;

/* *************************************************************************
 *                           ПЕРВАЯ ФУНКЦИЯ
 * *************************************************************************/ 

/**
 * @vars Начальная и конечная точки отрезка для первой функции.
 */
const real_t TARGET_1_A = 0.0, TARGET_1_B = 1.0;

/**
 * @fn  Возвращает значение целевой функции F(x) = sqrt(1 - x) - tan(x).
 */ 
real_t target_1(real_t x) {
    if ((1 - x) >= 0)
        return sqrt(1 - x) - tan(x);
    /*
     * NAN = Not A Number. Еще одна вещественная константа. 
     * Определена она в `math.h`. Используется для неопределенного значения.
     */ 
    return NAN;
}

/**
 * @fn  Возвращает значение функции f(x), из выражения x = f(x). 
 *      Уравнение x = f(x) эквивалентно уравнению F(x) = 0.
 *      Можно пробовать выразить f(x) = 1 - tan(x)*tan(x), 
 *      но в такой формулировке не выполнено достаточное условие сходимости.
 *      |f(x)'| = |-2 * tan(x) / (cos(x) * cos(x))| < 1, x ∈ [a, b] = [0, 1]
 *      Т.к |f(0.5)'| = |-2 * tan(0.5) / (cos(0.5) * cos(0.5))| = 1.41 > 1
 *      Если выражать функцию через atan(sqrt(1 - x)), то все получатся.
 *      Условие сходимости выполнено:
 *          |f(x)'| = |1/(2 * sqrt(1-x) * (x-2))| < 1, x ∈ [0, 1]
 * 
 */ 
real_t target_1_xfx(real_t x) {
    if ((1 - x) >= 0)    
        return atan(sqrt(1 - x));
    /*
     * NAN = Not A Number. Еще одна вещественная константа. 
     * Определена она в `math.h`. Используется для неопределенного значения.
     */ 
    return NAN;
}

/**
 * @fn Возвращает значение производной функции F(x) = sqrt(1 - x) - tan(x).
 */ 
real_t target_1_derivative(real_t x) {
    if ((1 - x) >= 0)
        return (-1 / (2 * sqrt(1 - x))) - (1 / (pow(cos(x), 2)));
    /*
     * NAN = Not A Number. Еще одна вещественная константа. 
     * Определена она в `math.h`. Используется для неопределенного значения.
     */ 
    return NAN;
}

/* *************************************************************************
 *                           ВТОРАЯ ФУНКЦИЯ
 * *************************************************************************/ 

/**
 * @vars Начальная и конечная точки отрезка для второй функции.
 */
const real_t TARGET_2_A = 0.5, TARGET_2_B = 1.0;

/**
 * @fn  Возвращает значение целевой функции F(x) = x + cos(x^0.52 + 2).
 */ 
real_t target_2(real_t x) {
    return x + cos(pow(x, 0.52) + 2);
}

/**
 * @fn  Возвращает значение функции f(x), из выражения x = f(x). 
 *      Уравнение x = f(x) эквивалентно уравнению F(x) = 0.
 *      Несмотря, что с этой функцией метод итераций сходится, 
 *      нужно проверять условие сходимости для этой функции. 
 *      Вообще везде не плохо бы проверять условие сходимости.
 */
real_t target_2_xfx(real_t x) {
    return -cos(pow(x, 0.52) + 2);
}

/**
 * @fn  Возвращает значение производной функции F(x) = x + cos(x^0.52 + 2).
 *      
 */ 
real_t target_2_derivative(real_t x) {
    return 1 - 0.52 * pow(x, - 0.48) * sin(pow(x, 0.52) + 2);
}

/* *************************************************************************
 *                           ЧИСЛЕННЫЕ МЕТОДЫ
 * *************************************************************************/ 

real_t dichotomy(fun_t fun, real_t a_0, real_t b_0) {
    real_t a = a_0;
    real_t b = b_0;
    while (fabs(a - b) > REAL_EPSILON) {
        real_t m = (a + b) / 2;
        if (fun(a) * fun(m) >= 0)
            a = (a + b) / 2;
        else if (fun(b) * fun(m) >= 0)
            b = (a + b) / 2;
    }
    return (a + b) / 2;
}

real_t iterations(fun_t fun, real_t a_0, real_t b_0) {
    real_t a = a_0;
    real_t b = b_0;
    real_t x_0 = (a + b) / 2;
    real_t x =  fun(x_0);
    while (fabs(x - x_0) >= REAL_EPSILON) {
        x_0 = x;
        x = fun(x_0);
    }
    return x;
}

/**
 * @fn Решает уравнение вида F(x) = 0 методом Ньютона.
 * 
 */ 
real_t newton(fun_t fun, fun_t derivative, real_t a_0, real_t b_0) {
    real_t a = a_0;
    real_t b = b_0;
    real_t x_0 = (a + b) / 2;
    real_t x = x_0 - (fun(x_0) / derivative(x_0));
    while (fabs(x - x_0) >= REAL_EPSILON) {
        x_0 = x;
        x = x_0 - (fun(x_0) / derivative(x_0));
    }
    return x;
}

int main() {
    /*
     * Вычисляем ширину эпсилон.
     */
    int epswidth = ceil(-log10(REAL_EPSILON));
    
    printf(
        "target_1 = 0, x = %.*f; dichotomy,  x ∈ [%f, %f]\n", 
        epswidth, 
        dichotomy(target_1, TARGET_1_A, TARGET_1_B),
        TARGET_1_A, TARGET_1_B
    );
    printf(
        "target_1 = 0, x = %.*f; iterations, x ∈ [%f, %f]\n", 
        epswidth, 
        iterations(target_1_xfx, TARGET_1_A, TARGET_1_B),
        TARGET_1_A, TARGET_1_B
    );
    printf(
        "target_1 = 0, x = %.*f; newton,     x ∈ [%f, %f]\n", 
        epswidth, 
        newton(target_1, target_1_derivative, TARGET_1_A, TARGET_1_B),
        TARGET_1_A, TARGET_1_B
    );
    printf(
        "target_2 = 0, x = %.*f; dichotomy,  x ∈ [%f, %f]\n",
        epswidth, 
        dichotomy(target_2, TARGET_2_A, TARGET_2_B),
        TARGET_2_A, TARGET_2_B
    );
    printf(
        "target_2 = 0, x = %.*f; iterations, x ∈ [%f, %f]\n",  
        epswidth, 
        iterations(target_2_xfx,  TARGET_2_A, TARGET_2_B),
        TARGET_2_A, TARGET_2_B
    );
    printf(
        "target_2 = 0, x = %.*f; newton,     x ∈ [%f, %f]\n", 
        epswidth, 
        newton(target_2, target_2_derivative, TARGET_2_A, TARGET_2_B),
        TARGET_2_A, TARGET_2_B
    );
    return (0);
}



