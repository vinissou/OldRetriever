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
 * TODO add auto zip release for Linux, because debian won't
 *      run the executable if it was compressed in Windows
 * TODO add current envoriment checks (compilers, libraries,
 *      etc)
 * TODO this is getting really ugly, it needs some refactoring
 * Creator: Vinícius Souza
 * Site:    https://github.com/vinissou
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//  silent mode will default to gcc in Windows?
//  TODO auto compiler list funtion among available

#if defined(_WIN32) || defined(_WIN64)
char *os = "WIN32";
#else
char *os = "else"; // for now
#endif

char *Args(int argc, char **argv);

int main(int argc, char **argv) {

    char *mode = Args(argc, argv);
    printf("\n\n %s \n\n", mode);

    // testing for future auto-select
    if (strcmp(mode, "--auto") == 0) {
        printf("\n gcc: %d\n", system("gcc --help"));
        printf("\n gcc: %d\n", system("gcc"));
    }

    // turn this into a struct
    char *compiler = NULL;
    char *flags = NULL;
    char *input = NULL;
    char *output = NULL;

    if (strcmp(os, "WIN32") == 0) {
        if (strcmp(mode, "-cl") == 0) {
            compiler = "cl"; // TODO improve this
            input = ".\\src\\app.c";
            flags = "/O2 /Wall /analyze"; // don't use /TC
            output = "/Fe:build\\retriever.exe /Fo:build\\retriever.obj";
        } else {
            compiler = "clang";
            input = ".\\src\\app.c";
            flags = "-Wall -Wextra -Werror -pedantic -std=c99 -O3";
            output = "-o .\\build\\retriever.exe";
        }
    } else {
        system("dos2unix *"); // TODO make it portable
        system("dos2unix modules/*");
        compiler = "cc";
        input = "./src/app.c";
        output = "-o ./build/retriever";
        flags = "-Wall -Wextra -Werror -pedantic -std=c99 -O3";
    }

    if (compiler == NULL) {
        printf("\n COMPILER: %s NOT FOUND\n", compiler);
        return EXIT_FAILURE;
    }

    char command[500];
    sprintf(command, "%s %s %s %s", compiler, flags, input, output);
    printf("\n%s\n", command);
    system(command);
    return EXIT_SUCCESS;
}

// this will be expanded, for now is just preventing a segfaul in
// silent mode
char *Args(int argc, char **argv) {
    if (argc >= 2) {
        return argv[1];
    } else {
        return "NO_ARGS";
    }
}
