/***********************************************************
* Name: file.h
*
* Function: 
* Header for the file operations module
*
* Observations: 
* All the functions and variables of this modules are 
* global, because this is intended to deal with the main 
* file that will be edited by all the others modules, but 
* I might include an encapsulated mode in case it is needed
* in some uses. 
*
*
* Creator: Vinícius Souza
* Email:   vinissou.git@gmail.com
* Site:    https://github.com/vinissou
***********************************************************/
#include "file.c"


/* GLOBAL VARIABLES */
//extern char *DEST_NAME;
//extern char *SOURCE_NAME;
//
//extern FILE *DEST;
//extern FILE *SOURCE;
//
//extern long long SOURCE_SIZE;
//extern long long POSITION;



/* FUNCTIONS */
extern long long FileSize(const char *filename);
extern long long RewindPosition(long long position, const long long decrement);

extern void AdvanceFile(FILE *file, long long steps);
extern void DestInit(char *filename);
extern void RewindFile(FILE *file, const long long steps);
extern void SourceInit(char *filename);





