#include "errors_handler.h"


void error_handle(error_level_t level, char* message)
{
    if(message == NULL)
    {
        fputs("WARNING: No message given to error handler.", stderr);
        return;
    }

    switch(level)
    {
    case WARNING:
        fprintf(stderr, "WARNING: %s\n", message);
        break;
    case FATAL:
        fprintf(stderr, "FATAL: %s\n", message);
        exit(EXIT_FAILURE);
        break;
    default:
        break;
    }
}
