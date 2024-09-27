/***********************************************************
* Name: finderC.h >>> TODO SEPARATE THE MODULES
*
* Function: 
* Main library header that calls all the other functions
*
* Observations: 
* [SPECIFY HOW TO USE]
*
* Creator: Vinícius Souza
* Email:   vinissou.git@gmail.com
* Site:    https://github.com/vinissou
***********************************************************/
#include <stdlib.h>



/* Fazer funcão que chama as outras e inicializa somente uma vez
*  o BUFFER e preprocess para cada termo
ALLOC_BUFFER(TERM_LENGHT);     //MOVER ESSES DOIS PARA 
PreProcess(TERM, TERM_LENGHT); //O retriever.h
*/


//change this to the file module somehow
// I know this is ugly but so is Microsoft's supposedly
// POSIX support
#include <sys/stat.h>
#if defined(_WIN32) || defined(_WIN64) 
    #define fread _fread_nolock //might speed it up a little
    #define fseek _fseeki64            
    #define ftell _ftelli64
    #define stat _stat64
#endif



#define STANDART_ROWS 5 //keep it? >>> don't >> use dynamic


/*TODO make it print the percentage of reading even when the 
* program didn't found any matches*/



/* Data exchange structures */
struct search_term {
    char      *STR;
    long long  LENGHT;
    short      CHECK; //TODO maybe scrap it???
    long long  MATCHES; 
} search_term; //TODO down here might not be necessary, try wthout it


struct pfile {
    FILE      *PTR;
    char      *NAME;
    long long  SIZE;
    long long  POSITION;
} pfile;



/* GLOBAL VARIABLES */
struct search_term TERM = 
{
    .STR     = NULL,
    .LENGHT  = 0,
    .CHECK   = 0,
    .MATCHES = 0
};

struct pfile SOURCE = 
{
    .PTR  = NULL,
    .NAME = NULL,
    .SIZE = 0,
    .POSITION = 0
};

struct pfile DEST = 
{
    .PTR  = NULL,
    .NAME = NULL,
    .SIZE = 0,
    .POSITION = 0
};


//TODO prototypes to make this better and use extern 
#include "file.h"
#include "output.h"
#include "search.h"
#include "copy.h"



////
//struct search {
//    char      *TERM;
//    long long  TERM_LENGHT;
//    short      TERM_CHECK;
//    FILE      *SOURCE
//    char      *SOURCE_NAME;
//    long long  SOURCE_SIZE;
//    long long  SOURCE_POSITION;
//    FILE      *DEST;
//    char      *DEST_NAME;
//    long long  RETURN_POSITION[1]; //test it
//    char      *RETURN_BUFFER; //test it
//} search;
