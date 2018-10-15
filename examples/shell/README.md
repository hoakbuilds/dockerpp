# Kryshell

Usage of all shell built-in functions:
## sair / exit
Leaves the shell and displays some miscellanea.

## quemsoueu / whoami
Displays user info.

## PS1
Changes the shell's prompt to whatever is written after the = symbol.

Example:\
Kryshell>PS1=syntax\
syntax>

## cd [PATH]
Changes directory to path specified.

Example:\
Kryshell>cd /home/usr/

## socp [SRC] [DEST] 
Copies text content from SRC file to DEST file.

Example:\
Kryshell>socp /home/usr/Desktop/src.txt /home/usr/Desktop/dest.txt

## closefd [FILE]
Closes the given FILE descriptor.

Example:
closefd 1

## openfile [FILE] [MODE]
Opens a FILE descriptor. Note that you have to be in that FILE's directory.\
MODE: '0' for reading, '1' for writing, '2' for reading and writing.

Example:\
openfile thisshell.txt 0

## fileinfo
Displays information on the status of the STDOUT file pointer, if it's opened or not and what file descriptor it is using.\
The max number of open files the current process can have, the number of opened file descriptors as well as the file descriptors that are open and information regarding that file descriptor.\
Example:\
Kryshell>fileinfo\
STDOUT is open: File number 1.\
Current process has 1024 file limit.\
Process 10763 has 7 open files.\
Current opened file descriptors:\
0 - character device  -  MODE:  20620 (octal)  -  OWNERSHIP:  UID=1000   GID=5\
1 - character device  -  MODE:  20620 (octal)  -  OWNERSHIP:  UID=1000   GID=5\
2 - character device  -  MODE:  20620 (octal)  -  OWNERSHIP:  UID=1000   GID=5\
3 - regular file  -  MODE:  100644 (octal)  -  OWNERSHIP:  UID=1000   GID=1000

## soread [BYTES] [FDIN] [FDOUT]
Reads the first N specified BYTES from an opened file with file descriptor FDIN and writes them to the file descriptor FDOUT\
Example:\
soread 12 2 1\
will you pri\

## bits [VAL1] [OP] [VAL2]
let OP = { "&", "|", "^" }\
in OP = {\
    & = and\
    | = incluse OR\
    ^ = exclusive OR\
}

Example:\
bits 1 & 2\
0

bits 3 & 2\
2

## calc [VAL1] [OP] [VAL2]
OP = { "*", "/", "+", "-", "^" }

Example:\
calc 1 * 2\
2

calc 3 ^ 2\
8

## aviso [OP] [MESSAGE] [TIMER]
Waits for [timer in seconds] and then displays message from input.\
If used with [-t] argument, will execute threaded warning and you can still use the shell, when timer ends, message is displayed.\
	 
## rsi [CSV]
[on going work to calculate stock market / crypto asset rsi based on csv sheets]