#include "stack.h"


struct stack_t
{
    struct stack_t *prev;
    struct stack_t *next;
    void *data;
};

stack_t stack_new(void)
{
   return NULL;
}

void stack_push(stack_t *s, void *data)
{
    if (s)
    {
        stack_t p_p = *s;
        stack_t p_l = NULL;

        p_l = malloc(sizeof(*p_l));
        if (p_l)
        {
            p_l->data = data;
            p_l->next = NULL;
            p_l->prev = p_p;
            if (p_p)
                p_p->next = p_l;
            *s = p_l;
        }
        else
            error_handle(FATAL, "Unable to allocate memory\n");
    }
}

void *stack_pop(stack_t* s)
{
    void *ret = NULL;

    if (s && *s)
    {
        stack_t p_l = *s;
        stack_t p_p = p_l->prev;

        if (p_p != NULL)
            p_p->next = NULL;
        ret = p_l->data;
        free (p_l);
        p_l = NULL;
        *s = p_p;
    }

    return ret;
}

void stack_delete(stack_t *s)
{
   if (s && *s)
   {
      while (*s)
         stack_pop(s);
   }
}

bool_t stack_is_empty(stack_t s)
{
    return s == NULL;
}
