#define _SVID_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <dirent.h>
#include <math.h>

					/*CONSTANTS THAT MAY BE USEFUL*/

#define BG 0		  				/* used for background process*/
#define FG 1		  				/* used for foreground process*/
#define PIPE 2
#define BGPIPE 3
#define FGPIPE 4
#define LLFIOBUFF 256 				/* low level file input/output buffer size */
#define FILE_MODE ( S_IRUSR | S_IWUSR ) /* File permissions when using creat */

					/*ANSI COLOR AND TEXT FORMATTING CODES*/
#define KRYED              "\x1b[31m"
#define KRYREEN            "\x1b[32m"
#define KRYELLOW           "\x1b[33m"
#define KRYLUE             "\x1b[34m"
#define KRYAGENTA          "\x1b[35m"
#define KRYYAN             "\x1b[36m"
#define KRYESET            "\x1b[0m"
#define STYLE_BOLD         "\033[1m"
#define STYLE_NO_BOLD      "\033[22m"
#define STYLE_UNDERLINE    "\033[4m"
#define STYLE_NO_UNDERLINE "\033[24m"
#define FOLDER             "\033[1m\x1b[32m"



typedef struct{
	char msg[1024];
	char prompt[128];
	int tempo;
}Aviso_t;

typedef struct {
	int in;
	int out;
	int buffsize;
}Copiar_t;

typedef struct {
	char fonte[100];
	char destino[100];
}Copiarfd_t;

					/* HISTORY LIST OPERATION */


					/* SHELL OPERATION */
void printbi();
int parse (char *buf, char **args);
void redirects(int numargs, char *args[]);
void execute (char **args, int numargs);
int builtin (char **args, int numargs);
int ultimo (int numargs, char **args);
int containsPipe (int numArgs, char **args);
void sols(char *pathname);

					/* TEXT COPY */
void socp (char *src, char *dest);
int socpread (int src, int dest);
void soread (int n, int fdin, int fdout);
void cat (char* input, char* output);
void * socpwrapper(void *args);
void * socpreadwrapper(void *args);
int * socpread_t (int src, int dest, int buffersize);
void * socp_t(char *src, char* dest);


					/* FILE DESCRIPTORS */
int validfd (int fd);
void openfile (char *filename, int mode);
void closefd (int fd);
void fileinfo ();
int isjpeg( int fd );
int get_num_fds();

					/* MATHEMATICAL OPERATIONS */
void tworand ();
void calc(char *value1, char *op, char *value2);
void bits(char *value1, char *op, char *value2);

					/* STOCK MARKETS (ETC) TECHNICAL INDICATORS */
void rsi(char *filename, int periods, double top, double bottom );

					/* UTILITY FUNCTIONS */

void aviso(char *msg, int tempo);
void avisot(char *msg, int tempo, char *prompt);
void * avisowrapper(void *args);

					/* ADD SOME MUSIC, WHY NOT? */


