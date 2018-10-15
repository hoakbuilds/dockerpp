/*
	parse.c .:.
	partitions the Unix command (stored in the buffer) into arguments using blanks as explained below
*/

#include "shell.h"

int parse(char *buf, char **args)
{
	int counter=0;
	while ('\0' != *buf)
    {
		/* strip whitespace. Usa um NULL para indicar que o argumento anterior e. o ultimo */
		while (isspace((unsigned char)*buf))
		*buf++ = '\0';
		*args++ = buf;		/* salvaguarda argumento */
		counter++;
		while ((*buf != '\0') && (!isspace((unsigned char)*buf)))	/* salta sobre o argumento */
		buf++;
    }
    *args = (char *) NULL;	/* o ultimo argumento e. NULL */
    return counter;
}
