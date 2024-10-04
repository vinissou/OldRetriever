/***********************************************************
 * Name: app.h
 *
 * TODO Rewrite all the headers descriptions
 * Function:
 * Header file for the executable program that calls the
 * functions from the portable library retriever.h.
 *
 * Creator: Vinícius Souza
 * Site:    https://github.com/vinissou
 ***********************************************************/
#if defined(_WIN32) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <errno.h>
#include <stdio.h>

#include "modules/finderC.h"

#define FALSE 0
#define TRUE 1

struct options_status {
    short DEBUG;
    short COUNT;
    short LIMITERS;
    short LINES;
    short OUTPUT;
    short POSITIONS;
    short RANGE;
} options_status;
