#include "queue.h"

typedef struct queue_elem_type
{
     int val;
     struct queue_elem_type *next;

} queue_elem_t;


struct queue_type
{
     int length;

     struct queue_elem_type *begin;
     struct queue_elem_type *end;
};

typedef struct queue_type *queue_t;

queue_t queue_init()
{
     queue_t queue = malloc ( sizeof ( struct queue_type ) );

     queue->length = 0;

     queue->begin = NULL;
     queue->end = NULL;

     return queue;
}

void queue_add ( queue_t q, int value )
{
     if ( q->length )
          {
               q->end->next = malloc ( sizeof ( struct queue_elem_type ) );

               q->end->next->val = value;
               q->end->next->next = NULL;

               q->end = q->end->next;
          }
     else
          {
               q->begin = malloc ( sizeof ( struct queue_elem_type ) );

               q->begin->val = value;

               q->begin->next = NULL;

               q->end = q->begin;
          }

     q->length++;
}

int *queue_head ( queue_t q )
{
     return & ( q->begin->val );
}

int *queue_tail ( queue_t q )
{
     return & ( q->end->val );
}


void queue_clear ( queue_t q )
{
     int i;

     for ( i = 0; i < q->length; i++ )
          queue_remove ( q );
}


void queue_remove ( queue_t q )
{
     if ( q->length )
          {
               struct queue_elem_type *curr = q->begin->next;

               free ( q->begin );
               q->begin = curr;
               q->length--;
          }
}
int queue_size ( queue_t q )
{
     return q->length;
}

void queue_destroy ( queue_t q )
{
     queue_clear ( q );
     free ( q );
}

int main ( int argc, char *argv[] )
{
     queue_t my_queue = queue_init();

     queue_add ( my_queue, 100 );
     queue_add ( my_queue, 200 );
     queue_add ( my_queue, 300 );
     queue_add ( my_queue, 400 );

     printf ( "%d\n", queue_size ( my_queue ) );
     queue_remove ( my_queue );
     printf ( "%d\n", *queue_head ( my_queue ) );

     queue_destroy ( my_queue );

     return 0;
}
