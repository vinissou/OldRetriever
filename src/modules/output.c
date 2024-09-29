/***********************************************************
* Name: output.c
*
* Function: 
* Control all the file and stdout output operations.
*
* Observations: 
*
* Used functions and variables from other files:
*
* Creator: Vinícius Souza
* Site: https://github.com/vinissou
***********************************************************/

//TODO: substitute all the fread and fprintf for versions that don't dump
//everything on the memory??? >>> yes, the idea was to avoid very large line
                                //results overflowing the screen or the system
                                //maybe turning it in a option? maybe in the 
                                //advance module???




//TODO function to get the date from the system
//TODO implement a --silent and --verbose modes flags here

/// TODO change it to a struct 
// bugs output in openbsd if not checked
// it needs to become an arg option
unsigned long long  OUTPUT_MAX    = 200000; //TODO change for a dynamic value 
short int  OUTPUT_STDOUT = 0;
short int  OUTPUT_RETURN = 0; //implement return option

//TODO VVV does it need to be static???
static char *output_buffer = NULL;




/* Make this work with buffered chunks*/
//TODO this is used in copy.h, FIX THIS >>> copy it there
char *ReturnOutput(FILE *file, const char *fmt, ...) //eliminate it? 
{
    unsigned long long output_size = 0;
    va_list arg;

    output_buffer = realloc(output_buffer, OUTPUT_MAX);

    va_start(arg, fmt);
    output_size = vsnprintf(output_buffer, OUTPUT_MAX, fmt, arg);
    va_end(arg);

    if(output_size < OUTPUT_MAX){
        snprintf(output_buffer, output_size+1,"%s", output_buffer);
    }
    
    //TODO fix this VVV change it to a flag??
    //TODO you need to account for the --verbose
    //     even when it is printing to a file??
    if(file != NULL){
        fprintf(file ,"%s" ,output_buffer);
    }

    return output_buffer;
}


/***********************************************************
* Name: NotFound
* 
* Function: print the message to the file and the STDOUT 
* that the search term was not found
* TODO this need to be deleted from copy.h and substituted
*      for a frag 
***********************************************************/
void NotFound(FILE *file,
        const char *term)
{
    printf("\nTERM \"%s\" NOT FOUND\n", term);
    if(OUTPUT_STDOUT == 0 && file != stdout)
        fprintf(file,"\nTERM \"%s\" NOT FOUND\n", term);
}


/***********************************************************
* Name: ReturnResults >>TODO change this function TODO 
*
* Function: 
* Prints the count of found matches and the percentage of 
* completion, while keeping the cursor in the same position 
* and if the match count  is over 1 million it shorten the 
* number to not flood the STDOUT
*
* Used functions and variables from other files:
* main.h: SOURCE_SIZE, WIN >>> TODO fix the sizes of int
*                                   of the whole program
* TODO take this out of copy.h 
***********************************************************/
void ReturnResults(const long long position,
                  const long long find_count)
{
    if(OUTPUT_STDOUT == 0){ 
        int percent   = ((((double)position) / SOURCE.SIZE)*100);
        fflush(stdout);              
        printf("\rComplete: %d%%  | Results found: %lld  " ,percent 
                                                          ,find_count);
    }
}


/***********************************************************
* Name: ReturnTotal
*
* Function: prints the total of matches found on the source
* file
*
* Observations: in the future this function will print the 
* total at the header in the beginning of the file
***********************************************************/
void ReturnTotal(FILE *file,
                const long long find_count)
{

    if(OUTPUT_STDOUT == 0)
        printf("\rComplete: 100%%");

    if(file != NULL && file != stdout)
        fprintf(file, "\n\nTOTAL RESULTS: %lld\n", find_count);
    
    printf("\n\n\n    TOTAL RESULTS: %lld\n", find_count);
    
}



