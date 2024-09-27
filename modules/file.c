/***********************************************************
* Name: file.c
*
* Function: 
* Contains all the functions that open, navigate an deal 
* with files attributes
*
* Observations: 
*
* Creator: Vinícius Souza
* Email:   vinissou.git@gmail.com
* Site:    https://github.com/vinissou
***********************************************************/

//long long POSITION = 0; >>> moved to finderC.h

//FILE *SOURCE      = NULL;    >>> moved to finderC.h
//char *SOURCE_NAME = NULL;    >>> moved to finderC.h 
//long long  SOURCE_SIZE = 0;  >>> moved to finderC.h 

//FILE *DEST        = NULL;>>> moved to finderC.h
//char *DEST_NAME   = NULL;>>> moved to finderC.h



/***********************************************************
* Name: FileSize
*
* Function: 
* Returns in bytes the size of the file contained on the
* struct stat st from the file stat.h
***********************************************************/
long long FileSize(const char *filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}




// TODO Add a new function to open files which will 
//      be edited
/***********************************************************
* Name: SourceInit
*
* Function: 
* Initializes all the respective variables related to the 
* input file 
*
* Observations:
* TODO deal with multiple sources possibilities
* 
*
***********************************************************/
void SourceInit(char *filename)
{
    SOURCE.PTR  = fopen(filename, "r");
    SOURCE.SIZE = FileSize(filename);
    SOURCE.NAME = filename;
}


/***********************************************************
* Name: DestInit
*
* Function: 
* Initializes all the respective variables related to the 
* output file 
*
* Observations: 
* TODO deal with multiple destinations possibilities
*
***********************************************************/
void DestInit(char *filename)
{
    if(filename != NULL){
        DEST.PTR  = fopen(filename, "a+");//add mode selection here
        DEST.NAME = filename;
    }
}


/***********************************************************
* Name: AdvanceFile
*
* Function: 
* Advance the file for the requested amounti fo characters.
*
***********************************************************/
void AdvanceFile(FILE *file, 
                 long long steps)
{
    const long long current_position = ftell(file);
    
    //TODO this can advance beyond the file's end, add 
    //     add something like this: 
    //     if ... || current_position+steps < FILE_SIZE
    if(current_position >= 0)
        fseek(file, (current_position + steps), SEEK_SET);
}


/***********************************************************
* Name: RewindFile 
*
* Function: 
* Rewind the file for the requested amount of characters.
***********************************************************/
void RewindFile(FILE *file,
                const long long steps)
{
    const long long current_position = ftell(file);

    if((current_position - steps) < 0)
        fseek(file, 0, SEEK_SET);
    else
        fseek(file, (current_position - steps), SEEK_SET);
}


/***********************************************************
* Name: RewindPosition
*
* Function: 
* Rewind a position indicator without going below zero
***********************************************************/
long long RewindPosition(long long position,
                   const long long decrement)
{
    position = (position - decrement);
    if(position < 0)
        position = 0;

    return position;
}




