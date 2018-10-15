#include "shell.h"

void redirects(int numargs, char *args[]){
	
	if(numargs <3) return;
	int fd;
	
	if(strcmp(args[numargs-2], "2>") == 0) {
		fd=creat(args[numargs-1], S_IWUSR | S_IRUSR); if(fd<0) perror("error");
		close(STDERR_FILENO);
		dup(fd);
		close(fd);
		args[numargs-2]=NULL;
		numargs -= 2;	
		if(numargs==1) return;
	}
	
	if(strcmp(args[numargs-2], ">>") == 0) {
		fd=open(args[numargs-1], O_WRONLY | O_APPEND); if(fd<0) perror("error");
		close(STDOUT_FILENO);
		dup(fd);
		close(fd);
		args[numargs-2]=NULL;
		numargs -=2;	
		if(numargs==1) return;
	}
	
	if(strcmp(args[numargs-2], ">") == 0) {
		fd=creat(args[numargs-1], S_IWUSR|S_IRUSR); if(fd<0) perror("error");
		close(STDOUT_FILENO);
		dup(fd);
		close(fd);
		args[numargs-2]=NULL;
		numargs -=2;	
		if(numargs==1) return;
	}
	
	if(strcmp(args[numargs-2], "<") == 0) {
		fd=open(args[numargs-1], O_RDONLY); if(fd<0) perror("error");
		close( STDIN_FILENO );
		dup(fd);
		close(fd);
		args[numargs-2]=NULL;
		numargs -=2;	
		if(numargs==1) return;
	}

}
