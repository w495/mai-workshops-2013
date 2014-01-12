#ifndef __STUD_H__
#define __STUD_H__

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#define STUDENT_USE_PROMPT 1

#define STUDENT_USE_WHITE_LINE 1


typedef char  name_t[32];

typedef char  group_t[8];

typedef enum {FALSE=0, TRUE=1} bool_t;

typedef enum {FEMALE = 0, MALE = 1} ismale_t;

typedef enum {NOT_PASSED = 0, PASSED = 1} passed_t;

typedef enum {SATISFACTORY = 3, GOOD = 4, EXCELLENT = 5} mark_t;

typedef struct __student__ {
    size_t      number;
    ismale_t    ismale;
    group_t     group;
    name_t      name;
    passed_t    physical_culture;
    passed_t    english; 
    mark_t      mathematical_analysis;
    mark_t      discrete_mathematics;
    mark_t      linear_algebra;
    mark_t      informatics;
    mark_t      history;
} student_t;


typedef enum {
    NULL_FILE_ERROR                     = -0x02,
    NULL_STUDENT_POINTER_ERROR          = -0x03,
    GENDER_SCANF_ERROR                  = -0x11,
    GROUP_SCANF_ERROR                   = -0x12,
    NAME_SCANF_ERROR                    = -0x13,
    PHYSICAL_CULTURE_SCANF_ERROR        = -0x14,
    ENGLISH_SCANF_ERROR                 = -0x15,
    MATHEMATICAL_ANALYSIS_SCANF_ERROR   = -0x16,
    DISCRETE_MATHEMATICS_SCANF_ERROR    = -0x17,
    LINEAR_ALGEBRA_SCANF_ERROR          = -0x18,
    INFORMATICS_SCANF_ERROR             = -0x19,
    HISTORY_SCANF_ERROR                 = -0x1A,
    GENDER_TYPE_ERROR                   = -0x11,
    GROUP_TYPE_ERROR                    = -0x12,
    NAME_TYPE_ERROR                     = -0x13,
    PHYSICAL_CULTURE_TYPE_ERROR         = -0x24,
    ENGLISH_TYPE_ERROR                  = -0x25,
    MATHEMATICAL_ANALYSIS_TYPE_ERROR    = -0x26,
    DISCRETE_MATHEMATICS_TYPE_ERROR     = -0x27,
    LINEAR_ALGEBRA_TYPE_ERROR           = -0x28,
    INFORMATICS_TYPE_ERROR              = -0x29,
    HISTORY_TYPE_ERROR                  = -0x2A,
} student_error_t;


#if STUDENT_USE_PROMPT == 1
    #define __STUDENT_PROMPT(...)    \
            __student_vfprintf (    \
                stderr,             \
                ##__VA_ARGS__       \
            )
# else
    #define __STUDENT_PROMPT(...) 1
#endif


#define __STUDENT_ERROR(...)    \
        __student_ferror   (    \
            stderr,           \
            __FILE__,           \
            __LINE__,           \
            __FUNCTION__,       \
            ##__VA_ARGS__         \
        )
        
        
bool_t isismale(ismale_t ismale){
    if((MALE == ismale) || (FEMALE == ismale))
        return TRUE;
    return FALSE;
}

bool_t ispassed(passed_t passed){
    if((NOT_PASSED == passed) || (PASSED == passed))
        return TRUE;
    return FALSE;
}
        
bool_t ismark(mark_t mark){
    if((SATISFACTORY == mark) || (GOOD == mark) || (EXCELLENT == mark))
        return TRUE;
    return FALSE;
}

int student_fprintf(FILE* outfile, student_t* student_pointer){
    if(!outfile){
        return NULL_FILE_ERROR;
    }
    if(feof(outfile)){
        return -2;
    }

    if(!student_pointer){
        return NULL_STUDENT_POINTER_ERROR;
    }

    fprintf(outfile, "%lu\t",      student_pointer->number);
    fprintf(outfile, "%-32s\t",   (char*)student_pointer->name);
    fprintf(outfile, "%c\t",      (char)student_pointer->ismale);
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
    student_error_t error_type = 0;
    int scan_status = -1;

    if(!infile){
        __STUDENT_ERROR("Null pointer to infile\n");
        return NULL_FILE_ERROR;
    }

    if(feof(infile)){
        return EOF;
    }

    if(!student_pointer){
        __STUDENT_ERROR("Null pointer to student pointer\n");
        return NULL_STUDENT_POINTER_ERROR;
    }

    scan_status = (
        (
               __STUDENT_PROMPT("%lu) \n", (student_pointer->number))
            && __STUDENT_PROMPT("name (string):                   ")
            && (error_type = NAME_SCANF_ERROR)
            && (1 == fscanf(infile, "%s", (char *)&(student_pointer->name)))
        )
        && (
                __STUDENT_PROMPT("ismale (f or m):                 ")
            && (error_type = GENDER_SCANF_ERROR)
            && (1 == fscanf(infile, "%d", (int *)&(student_pointer->ismale)))
            && (error_type = GENDER_TYPE_ERROR)
            && isismale(student_pointer->ismale)
        )
        && (
                __STUDENT_PROMPT("group (string):                  ")
            && (error_type = GROUP_SCANF_ERROR)
            && (1 == fscanf(infile, "%s", (char *)&(student_pointer->group)))
        )
        && (
                __STUDENT_PROMPT("physical_culture (0 or 1):       ")
            && (error_type = PHYSICAL_CULTURE_SCANF_ERROR)
            && (1 == fscanf(infile, "%d", (int *)&(student_pointer->physical_culture)))
            && (error_type = PHYSICAL_CULTURE_TYPE_ERROR)
            && ispassed(student_pointer->physical_culture)
        )
        && (
                __STUDENT_PROMPT("english (0 or 1):                ")
            && (error_type = ENGLISH_SCANF_ERROR)
            && (1 == fscanf(infile, "%d", (int *)&(student_pointer->english)))
            && (error_type = ENGLISH_TYPE_ERROR)
            && ispassed(student_pointer->english)
        )
        && (
                __STUDENT_PROMPT("mathematical_analysis (3, 4, 5): ")
            && (error_type = MATHEMATICAL_ANALYSIS_SCANF_ERROR)
            && (1 == fscanf(infile, "%d", (int *)&(student_pointer->mathematical_analysis)))
            && (error_type = MATHEMATICAL_ANALYSIS_TYPE_ERROR)
            && ismark(student_pointer->mathematical_analysis)
        )
        && (
                __STUDENT_PROMPT("informatics  (3, 4, 5):          ")
            && (error_type = INFORMATICS_SCANF_ERROR)
            && (1 == fscanf(infile, "%d", (int *)&(student_pointer->informatics)))
            && (error_type = INFORMATICS_TYPE_ERROR)
            && ismark(student_pointer->informatics)
        )
        && (
                __STUDENT_PROMPT("linear_algebra  (3, 4, 5):       ")
            && (error_type = LINEAR_ALGEBRA_SCANF_ERROR)
            && (1 == fscanf(infile, "%d", (int *)&(student_pointer->linear_algebra)))
            && (error_type = LINEAR_ALGEBRA_TYPE_ERROR)
            && ismark(student_pointer->linear_algebra)
        )
        && (
                __STUDENT_PROMPT("history  (3, 4, 5):              ")
            && (error_type = HISTORY_SCANF_ERROR)
            && (1 == fscanf(infile, "%d", (int *)&(student_pointer->history)))
            && (error_type = HISTORY_TYPE_ERROR)
            && ismark(student_pointer->history)
        )
        &&(
                __STUDENT_PROMPT("discrete_mathematics  (3, 4, 5): ")
            && (error_type = DISCRETE_MATHEMATICS_SCANF_ERROR)
            && (1 == fscanf(infile, "%d", (int *)&(student_pointer->discrete_mathematics)))
            && (error_type = DISCRETE_MATHEMATICS_TYPE_ERROR)
            && ismark(student_pointer->discrete_mathematics)
        )
    );
    
    if(!scan_status){
        __STUDENT_ERROR(" error = -0x%x\n", -error_type);
        return error_type;
    }

    scan_status = (
        STUDENT_USE_WHITE_LINE
        && feof(infile)
        && __STUDENT_PROMPT("\nPress any key to contimue or EOF to exit.\n")
        && getc(infile)
        && !feof(infile)
        && getc(infile)
    );

    return 1;
}

int student_scanf(student_t* student_pointer){
    return student_fscanf(stdin, student_pointer);
}

#endif /* __STUD_H__ */
