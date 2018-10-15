#include "shell.h"

void tworand(){
	
	char prompt[] = "Insira valor MAX.\n";
	char vmax[10];
	char buffer[10];
	int pid, Vmax, status, result;
	int fd[2];
	
	pipe(fd);
	
	if((pid= fork())==-1){
		perror("fork");
		exit(1);
	}
	
	
	if(pid==0){
		closefd(fd[0]);
		write(STDOUT_FILENO, prompt, (strlen(prompt)+1));
		scanf("%d", &Vmax);
		snprintf(vmax, 10, "%d",  Vmax);
		write(fd[1], vmax, sizeof(vmax));
	}else
	{	
		while (wait (&status) != pid);
		closefd(fd[1]);
		read(fd[0], buffer, sizeof(buffer));
		result = 1+rand()%atoi(buffer);
		snprintf(vmax, 10, "%d", result);
		write(STDOUT_FILENO, buffer, (strlen(buffer)));
		result = 1+rand()%atoi(buffer);
		snprintf(vmax, 10, "%d", result);
		write(STDOUT_FILENO, buffer, (strlen(buffer)));
	}

}

void calc(char *value1, char *op, char *value2){

	float val1 = atof(value1), val2 = atof(value2);

	const char mult = '*';
	const char div = '/';
	const char plus = '+';
	const char minus = '-';
	const char expon = '^';

	if( mult == *op ){
		printf("%f\n", (val1*val2));
	}else if( div == *op ){
		if(val2 == 0){
			printf("Division error: division by 0.\n");
		}else printf("%f\n", (val1/val2));
	}else if( plus == *op ){
		printf("%f\n", (val1+val2));
	}else if( minus == *op ){
		printf("%f\n", (val1-val2));
	}else if( expon == *op ){
		printf("%f\n", powf(val1, val2));
	}

}

void bits(char *value1, char *op, char *value2){

	int val1 = atoi(value1), val2 = atoi(value2);
	const char and = '&';
	const char inclOR = '|';
	const char exclOR = '^';
	//const char not = '~';

	if( and == *op ){
		printf("%d\n", val1&val2);
	}else if( inclOR == *op ){
		printf("%d\n", val1|val2);
	}else if( exclOR == *op ){
		printf("%d\n", val1^val2);
	}

}