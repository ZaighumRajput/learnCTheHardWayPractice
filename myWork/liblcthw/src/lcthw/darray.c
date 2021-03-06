#include "darray.h"
#include <stdlib.h>

DArray *DArray_create(size_t element_size, size_t initial_max) 
{
	DArray *array = malloc(sizeof(DArray));	
	check_mem(array);

	array->max = initial_max;
	check(array->max > 0, "You must set an initial max > 0.");

	//what is is sizeof(void *)
	array->contents = calloc(array->max, sizeof(void *));	
	check_mem(array->contents);
	
	array->end = 0;
	array->element_size = element_size;
	array->expand_rate = DEFAULT_EXPAND_RATE;
	
	return array;

error:
	DArray_destroy(array);
	
	return NULL;
}

void DArray_destroy(DArray * array)
{
	if(array) {
		if(array->contents){
			free(array->contents);
		}
		free(array);
	}

}


int DArray_expand(DArray * array)
{
	//Increase the size of the array, that is the memory allocated 
	//for contents
	size_t old_max = array->max;
	size_t new_max = old_max + array->expand_rate;
	//array->max = array->max + array->expand_rate;
	check(DArray_resize(array, new_max) == 0, "Could not resize");
	//void *memset(void *s, int c, size_t n);
	//fills the first n bytes of the memory area pointed to by s
	//with the constant byte c
	//adding n spaces with 0's filled in to 
	memset(array->contents + old_max, 0, array->expand_rate + 1);
	return 0;
error:
	return -1;
}

int DArray_contract(DArray * array)
{
	check(array != NULL, "Invalid Array");
	
	size_t new_size = (size_t)(array->end) < array->expand_rate ?
			array->expand_rate : array->end;

	check(DArray_resize(array, new_size + 1) == 0, "Could not resize");

	return 0;

error:
	return -1;
}

int DArray_push(DArray * array, void* val)
{
	int rc = 0;
	if(array->end >= array->max) {
		rc = DArray_expand(array);
		check(rc == 0, "could not expand array");
	}
	array->contents[array->end] = val;
	array->end++;
	return 0;
error:
	return -1;
}
void *DArray_pop(DArray * array)
{
	check(array->end -1 >= 0, "Attempt to pop from empty array.");
	
	void *element = DArray_remove(array, array->end -1);
	array->end--;

	if (array->end > (int)array->expand_rate &&
			array->end % array->expand_rate)
	{
		DArray_contract(array);
	}

	return element;
error: 
	return NULL;
}
	
	




