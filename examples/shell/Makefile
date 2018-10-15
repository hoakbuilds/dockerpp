
CC=cc
FLAGS=-c -Wall
LIBS=-lm -pthread -lpthread
OBS=main.o execute.o parse.o socp.o files.o help.o redirects.o calcs.o rsi.o history.o cat.o aviso.o
 
 
all :  kryshell
 
main.o 		: src/shell.h src/main.c
	$(CC) $(FLAGS)  src/main.c
	
execute.o   : src/shell.h src/execute.c
	$(CC) $(FLAGS) src/execute.c
	
parse.o     : src/shell.h src/parse.c
	$(CC) $(FLAGS) src/parse.c
	
socp.o      : src/shell.h src/socp.c
	$(CC) $(FLAGS) src/socp.c

files.o     : src/shell.h src/files.c
	$(CC) $(FLAGS) src/files.c

help.o    	: src/shell.h src/help.c
	$(CC) $(FLAGS) src/help.c
	
redirects.o : src/shell.h src/redirects.c
	$(CC) $(FLAGS) src/redirects.c

calcs.o : src/shell.h src/calcs.c
	$(CC) $(FLAGS) src/calcs.c

rsi.o : src/shell.h src/rsi.c
	$(CC) $(FLAGS) src/rsi.c

history.o : src/shell.h src/history.c
	$(CC) $(FLAGS) src/history.c

cat.o : src/shell.h src/cat.c
	$(CC) $(FLAGS) src/cat.c

aviso.o : src/shell.h src/aviso.c
	$(CC) $(FLAGS) src/aviso.c
	
kryshell     : $(OBS)
	$(CC)  -o kryshell  $(OBS) $(LIBS)
	
clean limpar:
	rm -f kryshell *.o
	rm *~
	echo "Cleaning executables, compilation files and other trash."
