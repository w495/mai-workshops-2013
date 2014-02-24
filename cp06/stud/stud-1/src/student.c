/**
 * @file    student.с
 *          Файл с кодом для работы со структурой студента.
 *
 * @package student
 *          Работа со структурой студента.
 */

/*
 * Подключаем только один заголовочный файл.
 * В нем иже сделаны все нужные определения и включения.
 */

#include "student.h"

/**
 * @fn  Считывает информацию о студенте из файла `infile`.
 *      Возвращает код ошибки или `1` если все хорошо.
 *      Ситуации нулевых указателей и конца файла обрабатываются.
 *      Аналогично, обрабатываются проблемы при считывании какого-либо
 *      поля структуры.
 */
int student_fscanf(FILE* infile, student_t* student_pointer){

    if(!infile){
        __STUDENT_ERROR("infile is null pointer");
        return 0;
    }

    if(feof(infile)){
        return EOF;
    }

    if(!student_pointer){
        __STUDENT_ERROR("student_pointer is null");
        return -2;
    }

    __STUDENT_PROMPT("%lu) \n", (student_pointer->number));
    __STUDENT_PROMPT("name                 (\033[3mstring[32]\033[0m): ");


    /*
     * Опасный момент. Если мы введем слишком большую строку,
     * то мы перезапишем, что было до нее.
     *
     * Правильный путь:
     *      fscanf(infile, "%32s", (student_pointer->name))
     *
     * Еще лучше:
     *      char name[4096];
     *      fgets(name, sizeof(char) * 32, infile);
     *      sscanf(name, "%[^\n]", student_pointer->name);
     *
     * Или пишите свою функцию считывания строки.
     *
     */
    if (1 != fscanf(infile, "%s", (student_pointer->name))){
        return -3;
    }

    /**
     * Инициализируем, т.к. рискуем поиметь проблемы из-за приведения типов.
     * student_pointer->gender --- unsigned int, а мы считываем char.
     * Что произойдет:
     *      младшие байты перезапишем,
     *      а старшие останутся с мусором.
     */
    student_pointer->gender = 0;
    __STUDENT_PROMPT("gender                  (\033[3mf or m\033[0m): ");
    if (1 != fscanf(infile, " %c", (char *)&(student_pointer->gender))){
        return -4;
    }

    /*
     * Проверяем, все ли пользователь ввел нормально.
     * В данном случае, через fscanf он может ввести любой символ,
     * а нам нужны только `f` или `m`.
     */
    if(!is_gender_type(student_pointer->gender)){
        __STUDENT_ERROR("wrong  gender '%c'\n", student_pointer->gender);
        return -104;
    }

    __STUDENT_PROMPT("group                (\033[3mstring[8]\033[0m): ");

    /*
     * Опасный момент. Если мы введем слишком большую строку,
     * то мы перезапишем, что было до нее.
     *
     * Правильный путь:
     *      fscanf(infile, "%8s", (student_pointer->group))
     *
     * Еще лучше:
     *      char group[4096];
     *      fgets(group, sizeof(char) * 8, infile);
     *      sscanf(group, "%[^\n]", student_pointer->group);
     *
     * Или пишите свою функцию считывания строки.
     */

    if (1 != fscanf(infile, "%s", (student_pointer->group))){
        return -5;
    }

    __STUDENT_PROMPT("physical culture        (\033[3m0 or 1\033[0m): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->physical_culture))){
        return -6;
    }

    /*
     * Проверяем, все ли пользователь ввел нормально.
     * В данном случае, через fscanf он может ввести любое число.
     */
    if(!is_passed_type(student_pointer->physical_culture)){
        __STUDENT_ERROR("wrong  mark '%d'\n", student_pointer->physical_culture);
        return -106;
    }

    __STUDENT_PROMPT("english                 (\033[3m0 or 1\033[0m): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->english))){
        return -7;
    }

    /*
     * Проверяем, все ли пользователь ввел нормально.
     * В данном случае, через fscanf он может ввести любое число.
     */
    if(!is_passed_type(student_pointer->english)){
        __STUDENT_ERROR("wrong mark '%d'\n", student_pointer->english);
        return -107;
    }

    __STUDENT_PROMPT("mathematical analysis  (\033[3m2,3,4,5\033[0m): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->mathematical_analysis))){
        return -8;
    }

    if(!is_mark_type(student_pointer->mathematical_analysis)){
        __STUDENT_ERROR("wrong mark '%d'\n", student_pointer->mathematical_analysis);
        return -108;
    }

    __STUDENT_PROMPT("informatics            (\033[3m2,3,4,5\033[0m): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->informatics))){
        return -9;
    }

    if(!is_mark_type(student_pointer->informatics)){
        __STUDENT_ERROR("wrong mark '%d'\n", student_pointer->informatics);
        return -109;
    }

    __STUDENT_PROMPT("linear algebra         (\033[3m2,3,4,5\033[0m): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->linear_algebra))){
        return -10;
    }

    if(!is_mark_type(student_pointer->linear_algebra)){
        __STUDENT_ERROR("wrong mark '%d'\n", student_pointer->linear_algebra);
        return -110;
    }

    __STUDENT_PROMPT("history                (\033[3m2,3,4,5\033[0m): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->history))){
        return -11;
    }

    if(!is_mark_type(student_pointer->history)){
        __STUDENT_ERROR("wrong mark '%d'\n", student_pointer->history);
        return -111;
    }

    __STUDENT_PROMPT("discrete mathematics   (\033[3m2,3,4,5\033[0m): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->discrete_mathematics))){
        return -12;
    }

    if(!is_mark_type(student_pointer->discrete_mathematics)){
        __STUDENT_ERROR("wrong mark '%d'\n", student_pointer->discrete_mathematics);
        return -112;
    }

    __STUDENT_PROMPT("Press any key to contimue or \033[1mEOF\033[0m to exit.\n");
    getchar();
    getchar();

    return 1;
}


/**
 * @fn  Считывает информацию о студенте из файла `stdin`.
 *      Возвращает код ошибки или `1` если все хорошо.
 */
int student_scanf(student_t* student_pointer){
    return student_fscanf(stdin, student_pointer);
}

/**
 * @fn  Выводит информацию о студенте в файл `outfile`.
 *      Возвращает код ошибки или `1` если все хорошо.
 *      Ситуации нулевых указателей и конца файла обрабатываются.
 */
int student_fprintf(FILE* outfile, student_t* student_pointer){

    if(!outfile){
        __STUDENT_ERROR("outfile is null pointer");
        return -1;
    }

    if(feof(outfile)){
        __STUDENT_ERROR("end of outfile");
        return -2;
    }

    if(!student_pointer){
        __STUDENT_ERROR("student_pointer is null");
        return -3;
    }

    fprintf(outfile, "%lu\t",      student_pointer->number);
    fprintf(outfile, "%-32s\t",   (char*)student_pointer->name);
    fprintf(outfile, "%c\t",      (char)student_pointer->gender);
    fprintf(outfile, "%-8s\t",    (char*)student_pointer->group);
    fprintf(outfile, "%d\t",      (int)student_pointer->mathematical_analysis);
    fprintf(outfile, "%d\t",      (int)student_pointer->informatics);
    fprintf(outfile, "%d\t",      (int)student_pointer->linear_algebra);
    fprintf(outfile, "%d\t",      (int)student_pointer->history );
    fprintf(outfile, "%d\n",      (int)student_pointer->discrete_mathematics);
    return 1;
}

/**
 * @fn  Выводит информацию о студенте в файл `stdout`.
 *      Возвращает код ошибки или `1` если все хорошо.
 */
int student_printf(student_t* student_pointer){
    return student_fprintf(stdout, student_pointer);
}

/**
 * @fn  Выводит отладочное сообщение в форматом `format` в файл `outfile`
 *      Собственный аналог `printf`.
 */
int __student_vfprintf(FILE* outfile, const char* format, ... ){
    int status = 0;
    /*
     * Заводим массив необязательных аргументов.
     */
    va_list arguments;
    /*
     * Начинаем обработку необязательных аргументов.
     */
    va_start(arguments, format); 

    /*
     * Версия fprintf для работы с vargs.
     */ 
    status = vfprintf(outfile, format, arguments);

    /*
     * Завершаем обработку необязательных аргументов.
     */
    va_end(arguments);
    return status;
}

/**
 * @typedef Тип данных работы с функциями на отрезке.
 *          Удобно менять с `double` на `float`,
 *          и смотреть как меняются результаты.
 *          Например, становится легко видеть,
 *          что для `double` и для  `float` машинный эпсилон разный!
 *          Менять придется только здесь, не трогая остальной программы.
 */
int __student_ferror(
    FILE* outfile,              /* Куда выводим                     */
    const char* codefile,       /* Файл с исходным кодом            */
    int codeline,               /* Номер строки в исходниках        */
    const char* codefunction,   /* Название функции в исходниках    */
    const char* format,         /* Формат вывода                    */
    ...                         /* Необязательные аргументы         */
){
    int status = 0;

    /*
     * Заводим массив необязательных аргументов.
     */
    va_list arguments;

    /*
     * Начинаем обработку необязательных аргументов.
     */
    va_start(arguments, format); 

    /*
     * Обычный fprintf.
     */
    fprintf(
        outfile,
        "\n\033[1m\033[31mError\033[0m in \033[1m%s:%d\033[0m "
        "(function: \033[1m\033[32m%s\033[0m): ",
        codefile,       /* Файл с исходным кодом            */
        codeline,       /* Номер строки в исходниках        */
        codefunction    /* Название функции в исходниках    */
    );

    /*
     * Версия fprintf для работы с vargs.
     */
    status = vfprintf(outfile, format, arguments);

    /*
     * Завершаем обработку необязательных аргументов.
     */
    va_end(arguments);
    return status;
}
