/**
 * Кодирует текст по Цезарю с переменным ключом, равным номеру слова в тексте.
 * При кодировании участвуют только буквы латинского и цифры.
 * Множества строчных и прописных букв считаются зацикленными, так,
 * что 'z' + 1 = 'a',  'a' - 1 = 'z'.
 * Остальные символы в кодировании не участвуют.
 *
 *      $> gcc programme.c -pedantic -std=c89 -Wall
 *      $> ./a.out
 *      aaaa aaaa aaaa aaaa aaaa // <-- ввод
 *      aaaa bbbb cccc dddd eeee // <-- вывод
 *
 */

#include <stdio.h>

typedef enum { FALSE = 0, TRUE = 1 } bool_t;

/**
 * @fn  Проверяет является ли символ `symbol` буквой арабской десятичной цифрой.
 */
bool_t is_digit(short symbol){
    if (('0' <= symbol) && (symbol <= '9'))
        return TRUE;
    return FALSE;
}

/**
 * @fn  Проверяет является ли символ `symbol` прописной буквой.
 */
bool_t is_upper(short symbol){
    if (('A' <= symbol) && (symbol <= 'Z'))
        return TRUE;
    return FALSE;
}

/**
 * @fn  Проверяет является ли символ `symbol` строчной буквой.
 */
bool_t is_lower(short symbol){
    if (('a' <= symbol) && (symbol <= 'z'))
        return TRUE;
    return FALSE;
}

/**
 * @fn  Зацикливает множество символов
 *      'z' + 1 => 'a'
 *      'a' - 1 => 'z'
 */
short cycle(short symbol, short start, short stop){
    while (symbol < start){
        symbol = symbol + (stop - start + 1);
    }

    while (stop < symbol){
        symbol = symbol - (stop - start + 1);
    }
    return symbol;
}

/**
 * @fn Вычисляет новый символ, закодированный по цезарю, с учетом зацикливания.
 */
short offset(short symbol, int counter){
    short new_symbol = symbol + counter;
    if (is_digit(symbol)){
        return  cycle(new_symbol, '0', '9');
    }
    if (is_lower(symbol)){
        return  cycle(new_symbol, 'a', 'z');
    }
    if (is_upper(symbol)){
        return  cycle(new_symbol, 'A', 'Z');
    }
    return symbol;
}


int main() {
    /**
     * @var Переменная для введенного символа.
     */
    short symbol = 0;

    /**
     * @var Счетчик слов.
     *      На самом деле, тут тоже было бы достаточно типа unsigned short.
     */
    short counter = 0;

    /*
     * Читаем пока не конец файла.
     */
    while (EOF != (symbol = getchar())) {
        short new_symbol = offset(symbol, counter);
        putchar(new_symbol);
        if(' ' == symbol) {
            counter = (counter + 1) % 26;
        }
    }
    putchar('\n');

    return 0;
}
