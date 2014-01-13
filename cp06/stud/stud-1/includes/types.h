#ifndef __LIBTYPE_H__04463696__
#define __LIBTYPE_H__04463696__


typedef char  name_t[32];

typedef char  group_t[8];

typedef enum {FALSE, TRUE} bool_t;

typedef enum {MALE = (int)'m', FEMALE = (int)'f'} gender_t;

typedef enum {NOT_PASSED = 0, PASSED = 1} passed_t;

typedef enum {SATISFACTORY = 3, GOOD = 4, EXCELLENT = 5} mark_t;

bool_t is_gender_type(gender_t gender);

bool_t is_passed_type(passed_t passed);
        
bool_t is_mark_type(mark_t mark);


#endif /* __LIBTYPE_H__04463696__ */ 
