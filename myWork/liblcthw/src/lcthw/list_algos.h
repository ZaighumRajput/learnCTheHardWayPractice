#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>
#include <stdbool.h>

//function pointer to compare function
//note the const correctness
typedef int (*List_compare) (const void *a, const void *b);
bool List_bubble_sort(List * list, List_compare cmp);


#endif
