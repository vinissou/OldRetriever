/***********************************************************
 * Name: app.c
 *
 * Creator: Vinícius Souza
 * Site:    https://github.com/vinissou
 ***********************************************************/

#include "app.h"

/* Prototypes TODO >>> change them to app.h??*/
void ParseCmdLine(int argc, char *argv[]);
void FileChecker(void);
///////////////temp////////////////////////
void TEMPdebug(int argc, char *argv[]);

/* Variables and constants */
const char *usage;
const char *help;
struct options_status OPTIONS;

int main(int argc, char **argv) {
  ParseCmdLine(argc, argv);

  return (0);
}

/***********************************************************
 * Name: ParseCmdLine
 *
 * Function:
 * Parse the input from the command line and calls the
 * the selected options and files.
 *
 * Used functions and variables from other files:
 *
 ***********************************************************/
void ParseCmdLine(int argc, char *argv[]) {
  if (argc < 2) { // TODO move it to helpchecker or something like that?
    fprintf(stdout, "%s", usage);
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    fprintf(stdout, "%s", help);
    exit(EXIT_SUCCESS);
  }

  InitTerm(argv[2]);
  TERM.CHECK = 0; // TODO bm stuff, verify this >>> probably it needs
                  //      to be eliminated

  // TODO change this to another function?
  // TODO ADD --just-copy   || -jc OPTION
  // TODO ADD --ignore-case || -ic OPTION
  // TODO deal with unrecognize options like dest files without the -o
  // TODO combine --positions with other options
  for (int tmp = 1; tmp < argc; tmp++) {
    if (strcmp(argv[tmp], "-db") == 0)
      OPTIONS.DEBUG = true;

    if (strcmp(argv[tmp], "-c") == 0 || strcmp(argv[tmp], "--count") == 0)
      OPTIONS.COUNT = tmp;

    if (strstr(argv[tmp], "--limiters=") != NULL)
      OPTIONS.LIMITERS = tmp;

    if (strcmp(argv[tmp], "-l") == 0 || strcmp(argv[tmp], "--lines") == 0)
      OPTIONS.LINES = tmp;

    if (strcmp(argv[tmp], "-o") == 0 || strcmp(argv[tmp], "--output") == 0)
      OPTIONS.OUTPUT = tmp;

    if (strcmp(argv[tmp], "-p") == 0 || strcmp(argv[tmp], "--positions") == 0)
      OPTIONS.POSITIONS = tmp;

    if (strstr(argv[tmp], "--range=") != NULL)
      OPTIONS.RANGE = tmp;

    else if (OPTIONS.DEBUG == 0 && OPTIONS.COUNT == 0 &&
             OPTIONS.LIMITERS == 0 && OPTIONS.LINES == 0 &&
             OPTIONS.POSITIONS == 0 && OPTIONS.RANGE == 0) {
      fprintf(stdout, "\nOption not recognized\n");
      exit(EXIT_FAILURE);
    }
  }

  // TODO change this to another function?
  SourceInit(argv[3]);
  if (OPTIONS.OUTPUT > 0)
    DestInit(argv[OPTIONS.OUTPUT + 1]);
  else {
    OUTPUT_STDOUT = 1;
    DEST.PTR = stdout;
  }
  FileChecker();

  // TODO change to a switch case???
  if (OPTIONS.DEBUG > 0)
    TEMPdebug(argc, argv);
  if (OPTIONS.COUNT > 0) { // TODO add dest file headers
    OUTPUT_STDOUT = 0;
    CountOccurrences(SOURCE.PTR, TERM.STR); // TODO todo rename this
  }

  if (OPTIONS.LINES > 0)
    CopyLineResults(SOURCE.PTR, DEST.PTR, TERM.STR);

  if (OPTIONS.POSITIONS > 0)
    CopyPositions(SOURCE.PTR, DEST.PTR, TERM.STR);

  if (OPTIONS.RANGE > 0) { // TODO fix -1? already fixed?
    long long number = 0;
    char *buffer = malloc(strlen(argv[OPTIONS.RANGE]));
    sscanf(argv[OPTIONS.RANGE], "%8s %lld", buffer, &number);
    CopyRangeResults(SOURCE.PTR, DEST.PTR, TERM.STR, TERM.LENGHT, number);
  }

  if (OPTIONS.LIMITERS > 0) {
    char *buffer0 = malloc(strlen(argv[OPTIONS.LIMITERS]));
    char *buffer1 = malloc(strlen(argv[OPTIONS.LIMITERS]));

    sscanf(argv[1], "%11s %s", buffer0, buffer1);
    strtok(buffer1, ",");
    memcpy(buffer0, buffer1, strlen(argv[OPTIONS.LIMITERS]));
    buffer1 = strtok(NULL, ",");
    CopyLimitersResults(SOURCE.PTR, DEST.PTR, TERM.STR, buffer0, buffer1);
  }
}

void FileChecker(void) {
  if (!SOURCE.PTR || (!DEST.PTR && OUTPUT_STDOUT == 0)) {
    if (!SOURCE.PTR)
      fprintf(stderr, "\nERROR OPENING SOURCE FILE \"%s\": %s\n", SOURCE.NAME,
              strerror(errno));
    if (!DEST.PTR && (OUTPUT_STDOUT == 0))
      fprintf(stderr, "\nERROR OPENING DESTINATION FILE \"%s\": %s\n",
              DEST.NAME, strerror(errno));
    exit(EXIT_FAILURE);
  }
}

const char *usage =
    "\nUSAGE: retriever --option \"searchterm\" source destination\n"
    "\nFOR MORE INFORMATION: retriever --help\n\n";

const char *help = // TODO expand with all current options
    "\nHELP"
    "\n--------------------------------------------------------------"
    "\nUSAGE: retriever --option \"searchterm\" source destination\n"
    "\nDEBUG       -db (it needs to at the end, for now)"
    "\nLINES       -l "
    "\nPOSITIONS   -p "
    "\nCOUNT       -c"
    "\nLIMITERS   --limiters=\"token1\",\"token2\""
    "\nRANGE       -range=X,Y "
    "\n";

// TODO remove from this file?
void TEMPdebug(int argc, char *argv[]) {

  printf("\n----TEMP DEBUG----\n");
  for (int x = 0; x < argc; x++)
    printf("argv%d: %s\n", x, argv[x]);

  printf("\nFILE SIZE: %lld", SOURCE.SIZE);
  printf("\nFILE NAME: %s\n", SOURCE.NAME);

  // TODO Old junk that needs to be checked VVVV
  // InitTerm("film");
  // char *text = "iiiiiiiiiiiiiiiifilmasddasdsdadsadasd";
  // printf("\nTERM:%s TERM_SIZE: %lu text:%s text_size:%lu \n",
  //         TERM, TERM_LENGHT, text, strlen(text));
  // printf("ARGC = %d\n", argc);
  // printf("\nHorspool: %lld \n", HorspoolStr(TERM, TERM_LENGHT,
  //                                         text, strlen(text),0));
  // printf("\nBM STR: %lld\n", BoyerMooreStr(TERM, TERM_LENGHT,
  //                                        text, strlen(text),0));
  printf("\n----TEMP DEBUG END----\n");
}

/////////////temp////////////////////////
