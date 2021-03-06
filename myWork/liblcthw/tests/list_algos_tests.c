#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

//char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };

char *values[] = { "x", "y", "d", "a", "b" };
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

void print_list(List * words)
{
	LIST_FOREACH(words, first, next, cur) {
		if (cur != NULL) {
			debug("%s", (char *)cur->value);
		}
		else {
			debug("\n");
		}
	}
return;
}
char *test_print_list()
{
	List *words = create_words();
	print_list(words);

	return NULL;
}
char *test_bubble_sort()
{
	List *words = create_words();

	debug("Created list of words:");
	print_list(words);
	// should work on list of that needs sorting
	bool rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == false, "Bubble sort failed.");
	mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

	debug("After sorting:");
	print_list(words);
	// should work on list that is sorted
	rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == false, "Bubble sort on already sorted lists failed.");
	mu_assert(is_sorted(words), 
			"Words should already be sorted.");

	List_destroy(words);

	//should work on an empty list
	words = List_create(words);
	rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == false, "Bubble sort failed on an empty list");
	mu_assert(is_sorted(words), 
			"Words should be sorted if empty.")
	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	//mu_run_test(test_print_list);
	mu_run_test(test_bubble_sort);

	return NULL;
}

RUN_TESTS(all_tests);
