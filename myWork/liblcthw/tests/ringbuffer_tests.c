#include "minunit.h"
#include <lcthw/ringbuffer.h>

static RingBuffer *buffer = NULL;
char data[100] = { '\0' };

void *test_create()
{
	buffer = RingBuffer_create(100);
	
	mu_assert(buffer != NULL, "Failed to create ringbuffer.");

	return NULL;

}

void *test_destroy()
{

	RingBuffer_destroy(buffer);	
	return NULL;
}

void *test_read_write()
{
	mu_assert(RingBuffer_empty(buffer), "Should be empty.");
	mu_assert(!RingBuffer_full(buffer), "Should NOT be full.");
	debug("data is: %d, space is: %d", 
		RingBuffer_available_data(buffer),
		RingBuffer_available_space(buffer));
	
	mu_assert(RingBuffer_available_data(buffer) == 0,
			"Should have 0 data.");

	mu_assert(RingBuffer_available_space(buffer) == 100,
		"Should have 100 space.");

	int rc = RingBuffer_write(buffer, data, 100);
	mu_assert(rc == 100, "Failed to write full buffer.");
	mu_assert(RingBuffer_available_space(buffer) == 0, "Invalid space available");
	mu_assert(RingBuffer_available_data(buffer) == 100, "Invalid avaliable data");
	mu_assert(RingBuffer_full(buffer), "Buffer should be full.");
	mu_assert(!RingBuffer_empty(buffer), "Should not be empty");	
	RingBuffer_clear(buffer);

	rc = RingBuffer_write(buffer, "hello", sizeof("hello"));
	mu_assert(rc == sizeof("hello"), "Failed to write hello.");

	mu_assert(RingBuffer_available_data(buffer) == 6,
			"Should have 6 data.");
	mu_assert(RingBuffer_available_space(buffer) == 100 - 6,
			"Should have 100 space.");

	rc = RingBuffer_write(buffer, "Zaighum", sizeof("Zaighum"));

	mu_assert(!RingBuffer_empty(buffer), "Should not be empty.");

	mu_assert(!RingBuffer_full(buffer), "Should not be full.");

	rc = RingBuffer_read(buffer, data, sizeof("hello"));
	mu_assert(rc == sizeof("hello"), "failed to read the out");	  
	debug("data is %s", data);

	rc = RingBuffer_read(buffer, data, sizeof("Zaighum"));
	mu_assert(rc == sizeof("Zaighum"), "Failed to read out");
	mu_assert(RingBuffer_empty(buffer), "Should be empty");

	debug("data is %s", data);

	//bstring tests

	bstring data = bfromcstr("Hello Again");
	rc = RingBuffer_puts(buffer, data);
	bdestroy(data);
	mu_assert(rc != -1, "Failed to write a bstring");
	mu_assert(!RingBuffer_empty(buffer), "Should not be empty");
	data = RingBuffer_gets(buffer, 2);
	mu_assert(data, "Didn't get any bstring from gets.");
	mu_assert(bisstemeqblk(data, "He", 2), "Wrong gets results");
	bdestroy(data);

	data = RingBuffer_get_all(buffer);
	mu_assert(data, "didn't get any bstring from gets.");
	mu_assert(bisstemeqblk(data, "llo Again", 9),
			"Wrong get_all result.");
	bdestroy(data);

	return NULL;
			
}

char *all_tests()
{
	mu_suite_start();
	mu_run_test(test_create);

	mu_run_test(test_read_write);
	mu_run_test(test_destroy);

	return NULL;
}


RUN_TESTS(all_tests);
