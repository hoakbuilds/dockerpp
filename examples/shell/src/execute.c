#include "shell.h"

void execute (char **args, int numargs)
{	
	
	int pid, status;
	int code, indice=0, pidn, fd[2];
  
	code = ultimo (numargs, args);
	indice  = containsPipe(numargs, args);

	if ((pid = fork ()) < 0){											
		perror ("forks");						
											
		exit (1);							
	}
												
	if (pid == 0){

		redirects(numargs, args);

		if( indice <= 0){
			execvp (*args, args);					
		}else{
			args[indice]=NULL;

			pipe(fd);

			if(( pidn = fork()) <0 ){
				perror("forks");
				exit(1);
			}else if( pidn == 0 ){
				
				numargs = indice;
				printf("writing to pipe: %s numargs = %d\n",args[0],numargs);
				dup2(fd[1],STDOUT_FILENO);
				close(fd[0]);
				execvp(*args, args);

			}else {
			
			args = args + indice + 1;
			numargs = numargs - indice -1;

			printf("reading from pipe: %s numargs = %d\n",args[0],numargs);
			
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			execvp(*args, args);

			}

		}										
												
		perror (*args);							
												
		exit (1);								
	}										
											
	if(code==FG) while (wait (&status) != pid);

	return;
}

int ultimo ( int numargs, char **args ){

	if(args[numargs-1][0]=='&') {
		args[numargs-1]=NULL;
		return BG;
	}

	return FG;
}

int containsPipe (int numArgs, char **args){
	int index;

 	for (index = 0; index < numArgs; index++)
 		if (args[index][0] == '|'){
			return index;
 		}

 	return -1;
}
