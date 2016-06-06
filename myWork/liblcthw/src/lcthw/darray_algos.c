#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray * array, DArray_compare cmp)
{
	// void qsort(void *base, size_t nmemb, size_t size,
	// 			int(*compar)(const void *, const void *))
	qsort(array->contents, array->end, sizeof(void *), cmp);
        return 0;	
}
/*
int DArray_heapsort(DArray * array, DArray_compare cmp)
{
	return	heapsort(array->contents, array->end, sizeof(void *), cmp);
}

int DArray_mergesort(DArray * array, DArray_compare cmp)
{
	return	mergesort(array->contents, array->end, sizeof(void *), cmp);
}
*/


