#ifndef __dbg_h__
	#define __dbg_h__
	
	#include <stdio.h>
	#include <errno.h>
	#include <string.h>
	
	#ifdef NDEBUG
	#define debug(M, ...)
	#else
	//fprintf into stderr; could also be a file
	// any arguments in ... go into __VA_ARGS__
	#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n",\
	__FILE__, __LINE__, ##__VA_ARGS__)
	#endif
	
	#define clean_errno() (errno == 0 ? "None" : strerror(errno))
	
	#define log_err(M, ...) fprintf(stderr,\
	"[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
	clean_errno(), ##__VA_ARGS__)
	
	#define log_warn(M, ...) fprintf(stderr,\
	"[WARN] (%s:%d: errno: %s) " M "\n",\
	__FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
	
	#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n",\
	__FILE__, __LINE__, ##__VA_ARGS__)

	//will check if A is true and if not log error as M	
	#define check(A, M, ...) if(!(A)) {\
	log_err(M, ##__VA_ARGS__); errno=0; goto error; }
	
	//should be placed in any part of the code that should not run
	#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__);\
	errno=0; goto error; }
	
	//sees if pointer is valid
	#define check_mem(A) check((A), "Out of memory.")

	//Still checks and handles the error but doesn't report it
	#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
	errno=0; goto error; }
	
	#endif
