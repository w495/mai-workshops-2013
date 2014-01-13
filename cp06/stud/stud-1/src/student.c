#include "student.h"

int student_fprintf(FILE* outfile, student_t* student_pointer){
    
    if(!outfile){
        return -1;
    }

    if(feof(outfile)){
        return -2;
    }

    if(!student_pointer){
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

int student_printf(student_t* student_pointer){
    return student_fprintf(stdout, student_pointer);
}

int __student_vfprintf(FILE* outfile, const char* format, ... ){
    int status = 0;
    va_list arguments;
    va_start(arguments, format); 
    
    /*
     * Версия fprintf для работы с vargs.
     */ 
    status = vfprintf(outfile, format, arguments);
    va_end(arguments);
    return status;
}


int __student_ferror(
    FILE* outfile,  
    const char* codefile, 
    int codeline, 
    const char* codefunction, 
    const char* format, 
    ... 
){
    va_list arguments;
    int status = 0;
    va_start(arguments, format); 
    fprintf(outfile, "\n [!] Error in %s:%d (%s): ", codefile, codeline, codefunction);
    status = vfprintf(outfile, format, arguments);    
    va_end(arguments);
    return status;
}

int student_fscanf(FILE* infile, student_t* student_pointer){

    if(!infile){
        __STUDENT_ERROR("Null pointer to infile");
        return 0;
    }

    if(feof(infile)){
        return EOF;
    }

    if(!student_pointer){
        return -2;
    }

    __STUDENT_PROMPT("%lu) \n", (student_pointer->number));
    __STUDENT_PROMPT("name (string):                   ");
    if (1 != fscanf(infile, "%s", (char *)&(student_pointer->name))){
        return -3;
    }
    
    __STUDENT_PROMPT("gender (f or m):                 ");
    if (1 != fscanf(infile, " %c", (char *)&(student_pointer->gender))){
        return -4;
    }
    

    __STUDENT_PROMPT("group (string):                  ");
    if (1 != fscanf(infile, "%s", (char *)&(student_pointer->group))){
        return -5;
    }
    
    __STUDENT_PROMPT("physical_culture (0 or 1):       ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->physical_culture))){
        return -6;
    }
    
    __STUDENT_PROMPT("english (0 or 1):                ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->english))){
        return -7;
    }
    
    if(!is_passed_type(student_pointer->english)){
        __STUDENT_ERROR("wrong english mark '%d'\n", student_pointer->english);
        return -106;
    }

    __STUDENT_PROMPT("mathematical_analysis (3, 4, 5): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->mathematical_analysis))){
        return -8;
    }
    
    __STUDENT_PROMPT("informatics  (3, 4, 5):          ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->informatics))){
        return -9;
    }
    
    __STUDENT_PROMPT("linear_algebra  (3, 4, 5):       ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->linear_algebra))){
        return -10;
    }
    
    __STUDENT_PROMPT("history  (3, 4, 5):              ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->history))){
        return -11;
    }
    
    __STUDENT_PROMPT("discrete_mathematics  (3, 4, 5): ");
    if (1 != fscanf(infile, "%d", (int *)&(student_pointer->discrete_mathematics))){
        return -12;
    }
    
    __STUDENT_PROMPT("Press any key to contimue or EOF to exit.\n");
    getchar();
    getchar();
    
    return 1;
}

int student_scanf(student_t* student_pointer){
    return student_fscanf(stdin, student_pointer);
} 
