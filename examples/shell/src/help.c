#include "shell.h"

void printbi(){

	printf("\nUsage of all shell built-in functions:\n\n");
	printf(KRYYAN"sair\n"KRYESET);
	printf("Leaves the shell and displays some miscellanea.\n\n"KRYESET);
	printf(KRYYAN"quemsoueu 			\n"KRYESET);
	printf("Displays user info.\n\n");
	printf(KRYYAN"PS1				\n"KRYESET);
	printf("Changes the shell's prompt to whatever is written after the = symbol.\n%sExample:%s\nPS1=syntax\nsyntax>\n\n",KRYAGENTA,KRYESET);
	printf("%scd %s[PATH]%s  				\n",KRYYAN,KRYREEN,KRYESET);
	printf("Changes directory to path specified.\n%sExample:%s\ncd /home/usr/\n\n",KRYAGENTA,KRYESET);
	printf("%ssocp %s[OP] [SRC] [DEST] [BUFFSIZE]%s 		\n",KRYYAN,KRYREEN,KRYESET);
	printf("Copies text content from SRC file to DEST file.\nOmmit [OP] if threaded execution is undesired and only use [BUFFSIZE] if using [OP]='-t'\n%sExample:%s\nsocp /home/usr/Desktop/src.txt /home/usr/Desktop/dest.txt\nsocp -t /home/usr/Desktop/src.txt /home/usr/Desktop/dest.txt 1024\n\n" ,KRYAGENTA,KRYESET);
	printf("%sclosefd %s[FILE] %s 		\n",KRYYAN,KRYREEN,KRYESET);
	printf("Closes the given FILE descriptor.\n%sExample:%s\nclosefd 0 				\n(This would generally close the stdin, please do not try it at home)\n\n",KRYAGENTA,KRYESET);
	printf("%sopenfile %s[FILE] [MODE] %s	\n",KRYYAN,KRYREEN,KRYESET);
	printf("Opens a FILE descriptor. Note that you have to be in that FILE's directory.\n								\nMODE: '0' for reading, '1' for writing, '2' for reading and writing.\n%sExample:%s\nopenfile thisshell.txt\n\n",KRYAGENTA,KRYESET);
	printf(KRYYAN"fileinfo				\n"KRYESET);
	printf("Displays information on the status of the STDOUT file pointer,\nif it's opened or not and what file descriptor it is using.\nThe max number of open files the current process can have,\nthe number of opened file descriptors as well as the file descriptors that are open\nand information regarding that file descriptor.\n%sExample:%s\nfileinfo\nSTDOUT is open: File number 1.\nCurrent process has 1024 file limit.\nProcess 10763 has 7 open files.\nCurrent opened file descriptors:\n0 - character device  -  MODE:  20620 (octal)  -  OWNERSHIP:  UID=1000   GID=5\n1 - character device  -  MODE:  20620 (octal)  -  OWNERSHIP:  UID=1000   GID=5\n2 - character device  -  MODE:  20620 (octal)  -  OWNERSHIP:  UID=1000   GID=5\n3 - regular file  -  MODE:  100644 (octal)  -  OWNERSHIP:  UID=1000   GID=1000\n\n",KRYAGENTA,KRYESET);
	printf("%ssoread %s[BYTES] [FDIN] [FDOUT]%s	\n",KRYYAN,KRYREEN,KRYESET);
	printf("Reads the first N specified BYTES from an opened file with file descriptor FDIN and writes them to the file descriptor FDOUT\n%sExample:%s\nsoread 18 2 1\nwill you pri\n\n",KRYAGENTA,KRYESET);
	
}
