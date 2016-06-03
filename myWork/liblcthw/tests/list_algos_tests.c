#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };

#define NUM_VALUES 5

List *create_words()
{
	int i = 0; 
	List *words = List_create();

	for(i = 0; i < NUM_VALUES; i++) {
		List_push(words, values[i]);
	}

	return words;
}

int is_sorted(List * words)
{
	LIST_FOREACH(words, first, next, cur) {
		if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
			debug("%s %s", (char *)cur->value, (char *)cur->next->value);
			return 0;
		}
	}
	
	return 1;
}

char *test_bubble_sort()
{
	List *words = create_words();

	// should work on list that is sorted
	int rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == 0, "Bubble sort failed.");
	mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_bubble_sort);

	return NULL;
}

RUN_TESTS(all_tests);
