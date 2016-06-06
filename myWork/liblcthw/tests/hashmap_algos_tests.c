
#include <lcthw/bstrlib.h>

#include "minunit.h"

struct tagbstring test1 = bsStatic("test data 1");


char *test_fnv1a()
{
	uint32_t hash = Hashmap_fnv1a_hash(&test1);
	mu_assert(hash != 0, "Bad hash");

	return NULL;
}


char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_fnv1a);
	return NULL;
}

RUN_TESTS(all_tests);
