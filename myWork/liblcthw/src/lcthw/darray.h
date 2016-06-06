#ifndef _DArray_h
#define _DArray_h
#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

//reference letter to row of streets
typedef struct DArray {
	int end;
	int max; //what is this?
	size_t element_size; // how big is each "house"
	size_t expand_rate; //when we have to n+1 what should it expand to?
	void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_max); 
void DArray_destroy(DArray * array);
int DArray_expand(DArray * array);
int DArray_contract(DArray * array);
int DArray_push(DArray * array, void* val);
void *DArray_pop(DArray * array);
//## MACROS ## 
#define DEFAULT_EXPAND_RATE 300
#define DArray_free(E) free((E))

//## STATIC Function for DArray ##
static inline void DArray_set(DArray * array, int index, void * element)
{
	check(array != NULL, "Invalid Array");
	check(index < array->max, "darray attempted to set past max");
	if(index > array->end){
		array->end = index;
	}
	array->contents[index] = element;
error:
	return;
}

static inline void *DArray_get(DArray *array, int index)
{
	//what can go wrong?
	check(array != NULL, "Invalid array.");
	check(index <= array->max, "index greater than array end");
	check(index >= 0, "Invalid index");

	return array->contents[index];

error: //fallthrough
	return NULL;
}

//put one new element on the array
static inline void *DArray_new(DArray * array)
{
	check(array->element_size > 0, "Can't use DArray_new on 0 size darrays");

	return calloc(1, array->element_size);

error:
	return NULL;
}

static inline void *DArray_remove(DArray * array, int index)
{
	check(array != NULL, "Invalid Array");
	check(index <= array->end, "Index greater than array end");
	check(index >= 0, "Invalid index");

	void *element = array->contents[index];
	
	array->contents[index] = NULL;

	return element;
error:
	return NULL;
}
static inline int DArray_resize(DArray * array, size_t newsize)
{
	array->max = newsize;
	check(array->max > 0, "The newsize must be >0.");

	// void *realloc(void *ptr, size_t size);
	// changes the size of the memory block pointed to by ptr
	// to size bytes.
	// The contents will be unchanged in the range from the start
	// of the region up to the minimum of the old and new size
	// if new size is larger than the old size, added memory is not initalized
	// if pointer is NULL this is just malloc
	void *contents = realloc(
			array->contents, array->max * sizeof(void *));

	array->contents = contents;

	return 0;

error:
	return -1;
}
#endif
