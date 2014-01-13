#ifndef __STUDENT_H__643505802__
#define __STUDENT_H__643505802__

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "types.h"

typedef struct __student__ {
    size_t      number;
    gender_t    gender;
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


#define __STUDENT_PROMPT(...)    \
        __student_vfprintf (    \
            stderr,             \
            ##__VA_ARGS__       \
        )
        
#define __STUDENT_ERROR(...)    \
        __student_ferror   (    \
            stderr,           \
            __FILE__,           \
            __LINE__,           \
            __FUNCTION__,       \
            ##__VA_ARGS__         \
        )

int student_fprintf(FILE* outfile, student_t* student_pointer);

int student_printf(student_t* student_pointer);

int __student_vfprintf(FILE* outfile, const char* format, ... );

int __student_ferror(
    FILE* outfile,  
    const char* codefile, 
    int codeline, 
    const char* codefunction, 
    const char* format, 
    ... 
);

int student_fscanf(FILE* infile, student_t* student_pointer);

int student_scanf(student_t* student_pointer);


#endif /* __STUDENT_H__643505802__ */
