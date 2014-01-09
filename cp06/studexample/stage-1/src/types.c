#include "types.h"

bool_t is_gender_type(gender_t gender){
    if((MALE == gender) || (FEMALE == gender))
        return TRUE;
    return FALSE;
}

bool_t is_passed_type(passed_t passed){
    if((NOT_PASSED == passed) || (PASSED == passed))
        return TRUE;
    return FALSE;
}
        
bool_t is_mark_type(mark_t mark){
    if((SATISFACTORY == mark) || (GOOD == mark) || (EXCELLENT == mark))
        return TRUE;
    return FALSE;
} 
