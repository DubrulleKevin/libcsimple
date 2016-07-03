#ifndef DEF_STACK
#define DEF_STACK

#include <stdlib.h>

#include "errors_handler.h"
#include "types.h"


typedef struct stack_t* stack_t;

stack_t stack_new(void);
void stack_push(stack_t *s, void *data);
void *stack_pop(stack_t *s);
void stack_delete(stack_t *s);
bool_t stack_is_empty(stack_t s);


#endif
