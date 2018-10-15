#include "shell.h"

void cat (char* input, char* output){

    int fd;

    char nome[]="cat";
    char *args[2];
    args[0] = nome;
    args[1] = NULL;

    fd = open(input, O_RDONLY|O_CREAT);
    if( fd < 0 ){ fprintf(stderr, "open error\n"); return; }

    dup2(fd, fileno(stdin));
    close( fd );

    fd = creat(output, FILE_MODE);

    if( fd < 0 ){ fprintf(stderr, "creat error\n"); return; }

    dup2(fd, fileno(stdout));
    close(fd);

    execvp(nome, args);

    return;

}