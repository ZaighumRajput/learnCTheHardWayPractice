
#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

//making a function pointer to lib_function
typedef int (*lib_function) (const char *data);

int main(int argc, char *argv[]){
    
    printf("Passed in %d arguments\n", argc);
    //check(argc == 0, "USAGE: ex29 libex29.so function data");

    //string to arguments
    char *lib_file = argv[1];
    char *func_to_run = argv[2];
    char *data = argv[3];

    //dlopen in dlfcn.h
    //void *dlopen(const char *filename, int flag);
    // All necessary relocations shall be performed when the object is first loaded.
    void *lib = dlopen(lib_file, RTLD_NOW);
    //dlerror returns the latest error from dlopen, dlsym, or dlclose
    check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());
   
    //dlysm takes a handle of the dynamic library returned by dlopn
    // and name of symbol name
    // and returns the address where that symbol is loaded into memory
    //void *dlsym(void *handle, const char *symbol);
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, 
            "Did not find %s function in the library %s: %s", func_to_run,
            lib_file, dlerror());

    int rc = 0;
    rc = func(data);

    check(rc == 0, "Function %s return %d for data: %s", func_to_run, 
            rc, dlerror());

    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

error:
    
    return 1;
}

