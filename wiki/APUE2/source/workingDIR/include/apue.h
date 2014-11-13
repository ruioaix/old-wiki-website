#include <stdio.h>  //printf
#include <stdlib.h> //exit
#include <string.h> //strlen
#include <unistd.h> //lseek, STDIN_FILENO, STDOUT_FILENO
#include <sys/stat.h> //stat




#define	MAXLINE	4096			/* max line length */
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
