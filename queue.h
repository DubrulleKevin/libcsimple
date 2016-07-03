#ifndef DEF_QUEUE
#define DEF_QUEUE


#include <stdlib.h>

#include "errors_handler.h"
#include "types.h"


typedef struct queue_t* queue_t;

queue_t queue_new(void);
void queue_post(queue_t *q, void *data);
void *queue_get(queue_t *q);
void queue_delete(queue_t *q);
bool_t queue_is_empty(queue_t q);


#endif
