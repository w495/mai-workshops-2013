#include "student.h"

#define DEFAULT_DATABASE_FILENAME "priv/student.db";

int main(int argc, char *argv[]) {

    char*       database_fname;
    FILE*       database_file;
    student_t   student;
    size_t      snumber = 1;

    
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

    if ((database_file = fopen(database_fname, "w+")) == NULL) {
        perror(database_fname);
        return 1;
    }

    student.number = 1;
    while (student_scanf(&student) == 1) {
        fwrite(&student, sizeof(student), 1, database_file);
        student.number = ++snumber;
    }

    fflush(database_file);
    rewind(database_file);

    while (fread(&student, sizeof(student), 1, database_file)){
        student_printf(&student);
    }
    
    fclose(database_file);
    return 0;
}
