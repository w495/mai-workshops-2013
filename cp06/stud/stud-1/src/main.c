/***
 * Простой пример работы с файлами.
 * Программа создает файл 'priv/student.db'
 * и заполняет его данными,
 * которые ввел пользователь.
 * Все это происходит в цикле до вводе EOF.
 * После этого, программа перековывает файл
 * и выводит его содержимое
 * в виде простой таблицы.
 */

/*
 * Подключаем только один заголовочный файл.
 * В нем иже сделаны все нужные определения и включения.
 */
#include "student.h"

#define DEFAULT_DATABASE_FILENAME "priv/student.db";


int main(int argc, char *argv[]) {

    /**
     * @var Имя файла.
     */
    char*       database_fname;

    /**
     * @var Файловый указатель.
     */
    FILE*       database_file;

    /**
     * @var Номер студента
     */
    size_t      snumber = 1;

    /**
     * @var Структура студента.
     */
    student_t   student;

    if (argc > 2) {
        fprintf(stderr, "you are wrong:");
        fprintf(stderr, "\n %s ", argv[0]);
        return 1;
    }

    if (argc == 1){
        database_fname = DEFAULT_DATABASE_FILENAME;
    }
    else{
        database_fname = argv[1];
    }

    /*
     * Откроем файл на запись и на обновление.
     * Если такой файл существует, то он затирается.
     * Если открыть не удалось, то ругаемся и выходим.
     */
    if ((database_file = fopen(database_fname, "w+")) == NULL) {
        perror(database_fname);
        return 1;
    }

    /*
     * В цикле читаем со входного потока,
     * и записываем в файл
     */
    student.number = snumber;
    while (student_scanf(&student) == 1) {
        fwrite(&student, sizeof(student), 1, database_file);
        student.number = ++snumber;
    }

    /**
     * Сбросили все изменения на диск.
     */
    fflush(database_file);

    /**
     * Перешли в начало файла.
     */
    rewind(database_file);

    /**
     * Читаем из файла и записываем в выходной поток.
     */
    while (fread(&student, sizeof(student), 1, database_file)){
        student_printf(&student);
    }


    /*
     * Файлы всегда нужно закрывать.
     */
    fclose(database_file);
    return 0;
}
