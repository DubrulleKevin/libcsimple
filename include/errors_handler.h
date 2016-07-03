#ifndef DEF_ERRORS_HANDLER
#define DEF_ERRORS_HANDLER


#include <stdio.h>
#include <stdlib.h>


typedef enum error_level_t
{
    WARNING,
    FATAL
} error_level_t;

void error_handle(error_level_t level, char* message);


#endif
