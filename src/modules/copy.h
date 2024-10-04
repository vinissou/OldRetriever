/***********************************************************
* Name: copy.h
*       TODO >>> maybe change it to navigator or something 
*                and move all the fprintif and messages 
*                outside >>> the function just return a 
*                position and a state and the output can
*                parse it? 
* Function: 
* This file contains all the functions that copy the text 
* from the source file to the destine file or the stdout 
*
* Creator: Vinícius Souza
***********************************************************/
// TODO move all the fprintfs para outuput.h, so it can be 
//      used as a module 

//TODO move this to OUTPUT too and use the dynamic number of 
//     current columns of the terminal
static const char *divider = 
"\n----------------------------------------"
"----------------------------------------\n";


/* disable the information output and just copy the data */
short JUST_COPY = 0; //TODO move all the related operations to output.h

//long long   TERM.MATCHES = 0; moved to finderC.h

//static long long SOURCE.POSITION  = 0; moved to finderC.h


/***********************************************************
* Name: MatchChecker
*
* Function: 
* It manage the results of FindNext in order to determine 
* if is the last match or if no matches were found and sends
* the results to the file and stdout.
* 
* TODO rethink this whole thing <<<<<<<<<<<
*      it doesn't stop and the return values are too 
*      cryptic
* TODO maybe turn the  -1, 0 ,1 into precompiler flags?
* TODO move this to output.h or search???
* Used functions and variables from other files:
* search.h: FindNext
* output.h: NotFound, ReturnTotal, ReturnResults
***********************************************************/
short MatchChecker(FILE *source, 
                   FILE *destination, 
                   const char *term)
{
    SOURCE.POSITION  = FindNext(source, term);

    if(SOURCE.POSITION < 0){
        if(TERM.MATCHES <= 0){
            NotFound(destination, term);
            return -1;
        }
        else{
            ReturnTotal(destination, TERM.MATCHES); //CHANGE THIS BECAUSE OF LIMITERS???
            return 0;
        }
    }
    
    TERM.MATCHES++;
    ReturnResults(SOURCE.POSITION, TERM.MATCHES);
    return 1;
}


/***********************************************************
* Name: CopyPositions
*
* Function: print the marched positions of the search term
* on the source file to the destination file.
* 
* Used functions and variables from other files:
* file.h: AdvanceFile //TODO change it to getc
***********************************************************/
void CopyPositions(FILE *source, 
                   FILE *destination, 
                   const char *term)
{
    
    if (JUST_COPY != 1){ //change all this to the output.h
        fprintf(destination ,"%sPositions of \"%s\" in \"%s\"%s"
                            ,divider ,term ,SOURCE.NAME, divider);
    }

    while (1){
        if (MatchChecker(source, destination, term) <= 0)
            break;
        
        SendToOutput(destination,"\n%lld", SOURCE.POSITION);
        AdvanceFile(source, 1);
    }
}


/***********************************************************
* Name: CopyLimitersResults
*
* Function: print to a file the results with all the content 
* present between the determined limiters, if it finds 
* multiples results between the same limiters will print it 
* just one time.
*
* Used functions and variables from other files:
* file.h:  AdvanceFile //TODO change it to getc
* search.h:  FindNext, NextPosition, PreviousPosition, 
* output.h: NotFound, ReturnTotal, ReturnResults
***********************************************************/
void CopyLimitersResults(FILE *source, 
                         FILE *destination, 
                   const char *term,
                   const char *first_limiter,
                   const char *last_limiter)
{
    long long position       = 0; //TODO change for a version that can 
    long long begin_position = 0; //TODO begin in the middle of the file???
    long long end_position   = 0;
    long long find_count     = 0;
   
    if (JUST_COPY != 1){
        fprintf(destination ,"%sResults of the search for \"%s\" in \"%s\""
                             "\nwith the limiters \"%s\" and \"%s\"%s"
                            ,divider ,term ,SOURCE.NAME 
                            ,first_limiter ,last_limiter ,divider);
    }

    while(1){
       position = FindNext(source, term);
       if(position < 0 || begin_position < 0 || end_position < 0){
           if(find_count <= 0)
               NotFound(destination, term);
           else
               ReturnTotal(destination, find_count);
           break;
       }

       if(position < end_position){
           AdvanceFile(source, (end_position - position));
           continue;
       }

       end_position   = NextPosition(source, last_limiter);
       begin_position = PreviousPosition(source, first_limiter);

       if(end_position   < position ||
          begin_position > position){
           AdvanceFile(source, 1);//TODO it's really necessary??
           continue;
       }

       if(position < end_position && position > begin_position){ 
           find_count++;
           ReturnResults(position, find_count);
           char *buffer = ReturnLimitersRange(source, position  
                                             ,first_limiter ,last_limiter);
           if (JUST_COPY != 1){
               SendToOutput(destination, "\nPosition %lld to %lld:\n%s"
                                  ,begin_position  ,end_position ,buffer);
           }
           else{
                SendToOutput(destination, "\n%s",buffer);
           }
       }
       AdvanceFile(source, 1);
    }
}


/***********************************************************
* Name: CopyLineResults
*
* Function: print the whole line of the matched terms found
* on the source file to the destination file, the line will
* copied lu one time if there is more than one result per
* line 
*
* Used functions and variables from other files:
* file.h:  AdvanceFile //TODO change it to getc
* search.h:  FindNext, NextPosition 
* output.h: NotFound, ReturnTotal, ReturnResults
***********************************************************/
//TODO
//TODO JUST USE \n AS LIMITERS!!!!!!!!!
//TODO E O EOF??? FAZER ESQUEMA PARA ACHAR
void CopyLineResults(FILE *source, 
                     FILE *destination, 
                     const char *term)
{
    //long long previous_position  = 0; //check this, it's not used?
    long long begin_position     = 0;
    long long end_position       = 0;

    if (JUST_COPY != 1){
        fprintf(destination ,"%sLines of the results of \"%s\" in \"%s\":%s"
                            ,divider ,term ,SOURCE.NAME ,divider);
    }
   
    while (1){
        if (MatchChecker(source, destination, term) <= 0)
            break;
        if (SOURCE.POSITION < end_position){
            long long difference = (end_position - SOURCE.POSITION);
            //previous_position = (SOURCE.POSITION + difference);
            AdvanceFile(source, difference);
            continue;
        }
       
        const char *buffer = ReturnLine(source, SOURCE.POSITION);

        end_position   = NextPosition(source, "\n");
        begin_position = (end_position - ((long long) strlen(buffer)));
        if (JUST_COPY != 1){
            SendToOutput(destination 
                        ,"\nLine from the position %lld to %lld:\n%s"
                        ,begin_position ,end_position ,buffer);
        }
        else{
            SendToOutput(destination, "\n%s",buffer);
        }

        ReturnResults(SOURCE.POSITION, TERM.MATCHES);
        AdvanceFile(source, 1); //TODO it's really necessary???
    }
}


/***********************************************************
* Name: CopyRangeResults 
*
* Function: print to a file  the results with the determined 
* range of characters before and after the matched term.
*
* Used functions and variables from other files:
* file.h:  AdvanceFile //TODO change it to getc
* search.h:  FindNext
* output.h: NotFound, ReturnTotal, ReturnResults
***********************************************************/
void CopyRangeResults(FILE *source, 
                      FILE *destination, 
                      const char *term,
                      const long long  term_lenght,
                      const long long  range)
{
    long long begin_position = 0;
    long long end_position   = 0;
    
    if (JUST_COPY != 1){
        fprintf(destination ,"%sPositions of \"%s\" in \"%s\" "
                             "\nwith a range of %lld characters%s"
                            ,divider ,term ,SOURCE.NAME ,range ,divider);
    }

    while (1){
        if (MatchChecker(source, destination, term) <= 0)
            break;
        
        begin_position = RewindPosition(SOURCE.POSITION, (range+1));
        end_position   = (SOURCE.POSITION + (term_lenght-2) + range);
        
        const char *buffer = ReturnPositionRange(source 
                                                ,begin_position 
                                                ,end_position);
        if (JUST_COPY != 1){
            SendToOutput(destination ,"\nPosition %lld to %lld:\n%s" 
                                ,begin_position ,end_position ,buffer);
        }
        else{
            SendToOutput(destination, "\n%s", buffer);
        }
        
        AdvanceFile(source, term_lenght);//TODO it's really necessary???
    }
}



//TODO insert a output total table to the output file with some stats 
//     about the file
void CountOccurrences(FILE *file, const char *term)
{
    while (1){
        if (MatchChecker(file, stdout, term) <= 0){
            break;
            ReturnResults(SOURCE.POSITION, TERM.MATCHES);
        }
        
        AdvanceFile(file, sizeof(term));//TODO it's really necessary???
    }
    ReturnTotal(stdout,TERM.MATCHES);
}

