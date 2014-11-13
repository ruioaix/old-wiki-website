#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define	Buffsize 10241234

int main(){
    char buf[Buffsize];
    int i=0;
    ssize_t n;
    printf("test\n");
    for(;i<Buffsize;i++)
        buf[i]='a';
    printf("test\n");
    int fd=open("10MfileA",O_RDWR|O_CREAT|O_TRUNC, FILE_MODE);
    printf("test\n");
    if((n=write(fd, buf, Buffsize))==-1)
        err_sys("write error");
    exit(0);
}

