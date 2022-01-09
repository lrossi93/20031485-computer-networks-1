/*===PROGETTO DI RETI 1 DI LORENZO ROSSI, matr. 20031485 - HEADER===*/

/*===DIRETTIVE===*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

/*===DIMENSIONI MASSIME===*/
#define BUFFER_DIM 512
#define HIST_DIM 62

/*===MESSAGGI DI INIZIO/FINE COMUNICAZIONE===*/
static char WELCOME_MSG[32] = "BENVENUTO/A DAL SERVER!";
static char GOODBYE_MSG[32] = "ARRIVEDERCI DAL SERVER!";

/*===MESSAGGI DI ESITO===*/
static char OK[4] = "OK";
static char ERR[4] = "ERR";
static char END[4] = "END";

/*===MESSAGGI DI TIPO===*/
static char START[8] = "START";
static char TEXT[8] = "TEXT";
static char HIST[8] = "HIST";
static char EXIT[8] = "EXIT";
static char QUIT[8] = "QUIT";
static char SYNTAX[8] = "SYNTAX";

/*===MESSAGGI DI ERRORE===*/
static char ERR_INVALID_COMMAND[32] = "COMANDO NON VALIDO";
static char ERR_INVALID_COUNTER[64] = "CONTATORE NON PRESENTE O NON VALIDO";
static char ERR_WRONG_COUNTER[64] = "CONTATORE NON CORRISPONDENTE AL NUMERO DEI CARATTERI INSERITI";

/*===COMANDI CLIENT===*/
#define TEXT_BY_STRING 1
#define TEXT_BY_FILE 2
#define TEXT_BY_WORD 3
#define GET_HIST 4
#define EXIT_HIST 5
#define EXIT_NO_HIST 6
#define OPTIONS_AGAIN 7
#define WRONG_OPTION -1

/*===FUNZIONI CLIENT===*/
void print_file(char *filename);
int valid_chars(char *string);
void print_hashtogram(char *string);

/*===COMANDI SERVER===*/
#define COMMAND_TEXT 1
#define COMMAND_HIST 2
#define COMMAND_EXIT 3
#define COMMAND_QUIT 4
#define COMMAND_INVALID -1

/*===FUNZIONI SERVER===*/
void string_to_hist(char *string, int hist[], int dim);
void print_hist(char *string, int hist[], int dim);
