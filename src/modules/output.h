/***********************************************************
* Name: output.h
*
* Function: 
* Header for all the file/stdout output operations.
*
* Observations: 
*
* Creator: Vinícius Souza
* Site: https://github.com/vinissou
***********************************************************/
#include <stdarg.h>
#include "output.c" 


//TODO function to get the date from the system
//TODO implement a --silent and --verbose modes flags here



/* GLOBAL VARIABLES */
//TODO this VVVV is not used, it should
#if defined(_WIN32) || defined(_WIN64)
    #define BYTES 1024
    #define CURSOR_ON  ""
    #define CURSOR_OFF ""
#else 
    #define BYTES 1000
    #define CURSOR_ON  "\033[?25l"
    #define CURSOR_OFF "\033[?25h"
#endif

extern long long  OUTPUT_MAX;
extern short int  OUTPUT_STDOUT;
extern short int  OUTPUT_RETURN;


/* FUNCTIONS */
extern char *ReturnOutput(FILE *file, const char *fmt, ...);
extern void NotFound(FILE *file, const char *term);
extern void ReturnResults(const long long position, const long long find_count);
extern void ReturnTotal(FILE *file, const long long find_count);
