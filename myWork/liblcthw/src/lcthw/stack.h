#include <lcthw/list.h>

typedef List Stack; 

#define Stack_create List_create
#define Stack_destroy List_destroy
#define Stack_push List_push
#define Stack_pop List_pop

//will the preprocessor replace this correctly?
#define Stack_peek List_last
#define Stack_count List_count

//how do these two differ?
//LIST_FOREACH requries
//for stack, give the stack
//and the current
//why is it only necessary to specify just the current node
//because start is always known
//and next is always known, via stack_peek
#define STACK_FOREACH(S,V) LIST_FOREACH(S, last, prev, V)

//Initial Attempt
/*
static inline Stack *Stack_create()
{
//List_create() returns a pointer to a LIST
//Type cast?
	return (Stack*)List_create();

}

//stack push adds a "node" to the front of the list
//same as list push
void Stack_push(Stack *stack, void *value);

//void List_push(List * list, void *value);

//stack peek looks at the next value
//This is the same as List_first
#define List_first(A) ((A)->first != NULL ? (A)->first->value: NULL)
*/
