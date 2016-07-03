#include "queue.h"


struct queue_t
{
    queue_t prev;
    queue_t next;
    void *data;
};

queue_t queue_new(void)
{
    return NULL;
}

static void queue_prev(queue_t *q)
{
    if(q && *q)
        *q = (*q)->prev;
}

static void queue_first(queue_t *q)
{
    if(q && *q)
        while((*q)->prev)
            queue_prev(q);
}

static void queue_next(queue_t *q)
{
    if(q && *q)
        *q = (*q)->next;
}

static void queue_last(queue_t *q)
{
    if(q && *q)
        while((*q)->next)
            queue_next(q);
}

void queue_post(queue_t *q, void *data)
{
    queue_t p_l = NULL;
    queue_t p_p = NULL;

    queue_first(q);
    p_l = *q;
    p_p = malloc(sizeof(*p_p));
    if(!p_p)
        error_handle(FATAL, "Unable to allocate memory\n");
    p_p->data = data;
    p_p->next = p_l;
    p_p->prev = NULL;
    if(p_l)
        p_l->prev = p_p;
    *q = p_p;
}

void *queue_get(queue_t* q)
{
    void *ret = NULL;

    if(q && *q)
    {
        queue_t p_l = NULL;
        queue_t p_p = NULL;

        queue_last(q);

        p_l = *q;
        if(p_l)
            p_p = p_l->prev;
        ret = p_l->data;
        free(p_l);
        p_l = NULL;
        if(p_p)
            p_p->next = NULL;
        *q = p_p;
    }

    return ret;
}

void queue_delete(queue_t *q)
{
    if(q && *q)
    {
        while(*q)
            queue_get(q);
    }
}

bool_t queue_is_empty(queue_t q)
{
    if(q)
        return FALSE;
    else
        return TRUE;
}
