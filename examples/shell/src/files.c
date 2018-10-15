/*
	files.c .:.
	program file for file descriptor manipulations with the following functions:
	validfd(int fd)   			-- checks if a given file descriptor is valid
	openfile(char *filename)	-- opens a file with the given filename
	closefd(int fd)				-- closes a file with the given file descriptor
	fileinfo()  				-- returns info on the status of the stdout file pointer (opened or not:: NULL || !NULL)
								   what file descriptor it is using
							       the max number of open files the current process can have
							       the number of opened file descriptors and the file descriptors that are open
*/

#include "shell.h"

int validfd(int fd){
	
	return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
	
	/* on error, fcntl returns -1 and errno is set accordingly */

}

void openfile(char *filename, int mode){
	
	if( access(filename, F_OK) != -1 ) {
		switch(mode){ 
			case 0 : { 
				if(access(filename, R_OK) != -1 ){
					open(filename, O_RDONLY)!=-1 ? printf("Opened %s successfully with reading permission.\n", filename) : perror(filename); return;
				 } else perror("Error opening %s with reading permission:\n");
			 }
			case 1 : {
				if(access(filename, W_OK) != -1 ){
					open(filename, O_WRONLY)!=-1 ? printf("Opened %s successfully with writing permission.\n", filename) : perror(filename); return;
				 } else perror("Error opening %s with writing permission:\n");
			 }
			case 2 : {
				 if(access(filename, W_OK|R_OK) != -1 ){
					open(filename, O_RDWR)!=-1 ? printf("Opened %s successfully with reading and writing permission.\n", filename) : perror(filename); return;
				 } else perror("Error opening %s with reading and writing permissions:\n");
			 }
		}
	} else { 
		if( creat(filename, S_IRUSR|S_IWUSR)!=-1 ){
			switch(mode){ 
				case 0 : { 
					if(access(filename, R_OK) != -1 ){
						open(filename, O_RDONLY)!=-1 ? printf("Opened %s successfully with reading permission.\n", filename) : perror(filename); return;
					} else perror("Error opening %s with reading permission:\n");
				}
				case 1 : {
					if(access(filename, W_OK) != -1 ){
						open(filename, O_WRONLY)!=-1 ? printf("Opened %s successfully with writing permission.\n", filename) : perror(filename); return;
					} else perror("Error opening %s with writing permission:\n");
				}
				case 2 : {
					if(access(filename, W_OK|R_OK) != -1 ){
						open(filename, O_RDWR)!=-1 ? printf("Opened %s successfully with reading and writing permission.\n", filename) : perror(filename); return;
					} else perror("Error opening %s with reading and writing permissions:\n");
				}
			}
		}	
	}
	printf("Invalid opening mode.\nMODE: '0' for reading, '1' for writing, '2' for reading and writing.\n");
}
void closefd(int fd){
		
	if( close(fd)<0 ) perror(NULL);
	else printf("File descriptor %d closed successfully.\n", fd);
		
}

void fileinfo(){
	
	int i=0;
	struct rlimit rl;
	struct stat fd;
	
	if( fileno(stdout) != -1 ) printf("STDOUT is open: File number %d.\n", fileno(stdout) );
	else printf("STDOUT is closed.\n");
	
	if( getrlimit(RLIMIT_NOFILE, &rl) == 0 ) printf("Current process has %lld file limit.\n", (long long int)rl.rlim_cur);
	
	printf("Process %d has %d open files.\n", getpid(), get_num_fds());
	
	printf("Current opened file descriptors:\n");
	
	for(i=0; i<rl.rlim_cur; i++){
		if( validfd(i) ){
			fstat(i, &fd);
			printf("%d - ", i);
			switch (fd.st_mode & __S_IFMT) {
				case __S_IFBLK:  printf("block device  -");            break;
				case __S_IFCHR:  printf("character device  -");        break;
				case __S_IFDIR:  printf("directory  -");               break;
				case __S_IFIFO:  printf("FIFO/pipe  -");               break;
				case __S_IFLNK:  printf("symlink  -");                 break;
				case __S_IFREG:  printf("regular file  -");            break;
				case __S_IFSOCK: printf("socket  -");                  break;
				default:       printf("unknown?  -");                break;
			}
			printf("  MODE:  %lo (octal)  -  ", (unsigned long) fd.st_mode);
			printf("OWNERSHIP:  UID=%ld   GID=%ld\n", (long) fd.st_uid, (long) fd.st_gid);

		}
	}

}

void soread(int n, int fdin, int fdout){
	
	if( !validfd(fdin) ){
		perror("Input file descriptor is not valid.\n");
		return;
	}
	
	if( !validfd(fdout) ){
		perror("Output file descriptor is not valid.\n");
		return;
	}
	
	int w=0, nr=0, aux=0, diff=0;
	char buff[LLFIOBUFF];
	
	if(n>LLFIOBUFF){
		while( (nr=read(fdin, buff, LLFIOBUFF)>0) ) {
			w=write(fdout, buff, nr);
			if(w!=nr) perror("Error writing to output file descriptor.\n");
			aux+=w;
			diff=n-aux;
			if(LLFIOBUFF<diff) break;
		}
		if(diff<LLFIOBUFF){
			nr=read(fdin, buff, n);
			if(nr<0){ 
				perror("Error reading from input file descriptor.\n");
				return;
			}
			w=write(fdout, buff, nr);
			if(w!=nr){
				perror("Error writing to output file descriptor.\n");
				return;
			}
		}
		return;
	}
	
	nr=read(fdin, buff, n);
	if(nr<0){ 
		perror("Error reading from input file descriptor.\n");
		return;
	}
	w=write(fdout, buff, nr);
	if(w!=nr){
		perror("Error writing to output file descriptor.\n");
		return;
	}
	printf("\n");
	return;	
}

int get_num_fds()
{
     int fd_count;
     char buf[64];
     struct dirent *dp;

     snprintf(buf, 64, "/proc/%i/fd/", getpid());

     fd_count = 0;
     DIR *dir = opendir(buf);
     while ((dp = readdir(dir)) != NULL) {
          fd_count++;
     }
     closedir(dir);
     return fd_count;
}

int isjpeg( int fd ){

	unsigned char b[4];
	read(fd, b, 4);
	lseek(fd, 0, SEEK_SET);

	if ( b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && b[3] == 0xe0){
		return 1;
	}
	
	close(fd);

	return 0;
}


void sols(char* pathname){

	int count, i;
	struct dirent **files;
	struct stat file;
	char cwd[1024];

	if(pathname == NULL){
		if (getcwd(cwd, 1024)==NULL){
			printf(" Error getting path\n");
			exit(0);
		}
			
	printf("Current working directory = %s\n", cwd);
	count=scandir(cwd,&files, NULL,alphasort);
	/* If no files found, make a non-selectable menu item */
	if (count <= 0){
		printf("No files in this directory\n");
		exit(0);
	}
	printf("Number of files = %d\n",count);
	for (i=1;i<count+1;++i){

		if ( (strcmp(files[i-1]->d_name, ".") == 0) || (strcmp(files[i-1]->d_name, "..")==0) ){
			continue;
		} 
		if ( stat(files[i-1]->d_name, &file) == -1 ){
			printf("%s : could not stat\n",files[i-1]->d_name);
			continue;
		}
		if( S_ISDIR( file.st_mode ) ){
			printf(FOLDER"%s %s\n", files[i-1]->d_name,KRYESET );
			continue;
		}
		printf("%s",files[i-1]->d_name);
		putchar('\n');
	}
	return;
	}

	printf("Current working directory = %s\n", pathname);
	count=scandir(pathname,&files, NULL,alphasort);
	/* If no files found, make a non-selectable menu item */
	if (count <= 0){
		printf("No files in this directory\n");
		exit(0);
	}
	printf("Number of files = %d\n",count);
	for (i=1;i<count+1;++i){

		if ( (strcmp(files[i-1]->d_name, ".") == 0) || (strcmp(files[i-1]->d_name, "..")==0) ){
			continue;
		} 

		if( S_ISDIR( file.st_mode ) ){
			printf(KRYREEN" %s %s", files[i-1]->d_name,KRYESET);
			continue;
		}
		printf("%s",files[i-1]->d_name);
		putchar('\n');
	}

}

int file_select(struct dirent *entry){
	if ( (strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..")==0)) return(0);
	
	return(1);
}