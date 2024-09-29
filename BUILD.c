/***********************************************************
* Name: builder.c
*
* Experimental C only buid system, idea inspired by: 
* https://github.com/tsoding
*
* TODO change to a header for each target plataform
*      when it gets more complex??
* TODO check args for target platform and bits, if no 
*      if no arg is provided it will build for the current
*      one
*
* Creator: Vinícius Souza
* Site:    https://github.com/vinissou
***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

//this will become a compiler selector in the future
//might add cl one day
#if defined(_WIN32) || defined(_WIN64) 
    char *compiler = "clang";
    char *os = "WIN32";
    char *input = ".\\src\\app.c";
    char *output = "retriever.exe";
#else //for now
    char *compiler = "cc";
    char *os = "else"; //for now
    char *input = "./src/app.c";
    char *output = "retriever";
#endif


int main(int argc, char **argv) {
    char command[200];

    if (strcmp(os, "WIN32") != 0){ 
        system("dos2unix *");  //TODO make it portable
        system("dos2unix modules/*");
    }

    sprintf(command,"%s -Wall -Wextra -pedantic -std=c99 -O3 %s -o %s", compiler, 
            input, output);
    printf("\n%s\n", command);
    system(command);
    return 0;
}

