#include <stdlib.h>
#include <stdio.h>

typedef struct queue_type *queue_t;

queue_t queue_init();

void queue_add ( queue_t q, int value );

int *queue_head ( queue_t q );
int *queue_tail ( queue_t q );

void queue_clear ( queue_t q );
void queue_remove ( queue_t q );

int  queue_size ( queue_t q );

void queue_destroy ( queue_t q );
