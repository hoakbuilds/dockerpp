/*
	socp.c .:.
	creates the file descriptors to be used in copying from the SRC (source) to the DEST (destination) file
	and calls the copying function if there are no errors
 */

#include "shell.h"

void socp(char *src, char* dest){
		
		int source, destination;
		
		source = open(src, O_RDONLY);
		
		if( source<0 ){
			perror("Error opening source file.\n");
			return;
		}
		
		destination = creat(dest, S_IWUSR|S_IRUSR);
		
		if( destination<0 ){
			perror("Error creating destination file.\n");
			return;
		}
		
		socpread(source, destination);

}

int socpread (int src, int dest){

	int n, w;
	char buf[LLFIOBUFF];
	
	while( (n=read(src, buf, LLFIOBUFF)>0) ) {
		w=write(dest, buf, n);
		if(w!=n)
			perror("Error writing to destination file.\n");
	}
		if(n<0)
			perror("Error reading from source file.\n");
	
	return 0;

}

void * socpwrapper(void *args) {
    Copiarfd_t *cpy = (Copiarfd_t *) args;
    socp_t( cpy->fonte, cpy->destino);
    free(cpy);
	return NULL;
}


void * socpreadwrapper(void *args) {
    Copiar_t *cpy = (Copiar_t *) args;
    socpread_t( cpy->in, cpy->out, cpy->buffsize );
    free(cpy);
	return NULL;
}

void * socp_t(char *src, char* dest){
		
	int source, destination;
	int n, w;
	char buf[256];
	
	
	source = open(src, O_RDONLY);
	
	if( source<0 ){
		perror("Error opening source file.\n");
	}
	
	destination = creat(dest, S_IWUSR|S_IRUSR);
	
	if( destination<0 ){
		perror("Error creating destination file.\n");
	}	

	while( (n=read(source, &buf, 256)>0) ) {
		w=write(destination, buf, n);
		if(w!=n)
			perror("Error writing to destination file.\n");
	}
		if(n<0)
			perror("Error reading from source file.\n");
 
	return NULL;

}

int * socpread_t (int src, int dest, int buffersize){

	int n, w;
	char buf[buffersize];
	
	while( (n=read(src, buf, buffersize)>0) ) {
		w=write(dest, buf, n);
		if(w!=n)
			perror("Error writing to destination file.\n");
	}
		if(n<0)
			perror("Error reading from source file.\n");
	
	return 0;

}

