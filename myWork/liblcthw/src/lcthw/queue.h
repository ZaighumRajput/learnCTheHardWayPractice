#ifndef lcthw_queue_h
#define lchthw_queue_h
#include <lcthw/list.h>

#define Queue List
#define Queue_create List_create

#define Queue_destroy List_destroy
#define Queue_peek List_last

//enqueue
//add to the front
#define Queue_send List_unshift
//dequeue
//pop it from the end
#define Queue_recv List_pop
#define Queue_count List_count 

#define QUEUE_FOREACH(Q, C) LIST_FOREACH(Q, last, prev, C)
#endif
