#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>


/*******************************************************************
NAME
        mycat - concatenate files and print on the standard output

SYNOPSIS
        mycat [FILE] [SIZE]

DESCRIPTION
        Concatenate FILE to standard output.

        With no FILE, or when FILE is -, read standard input.

        SIZE      estabilish buffer size, 1024b by default        
********************************************************************/
int main(int argc, char *argv[]){
    ssize_t bytes;
    int buf_size = 1024;
    if(argc == 3) buf_size = atoi(argv[2]);
    char *buffer = malloc(buf_size);
    int fd;
    fd = (argc < 2) ? 0 : open(argv[1], O_RDONLY);
    if (fd == -1){
        printf("%s: file not found\n", argv[1]);
        exit(-1);
    }
    while((bytes = read(fd,buffer,buf_size)) > 0)
        write(1, buffer, bytes);
    close(fd);
    free(buffer);
    return 0;
}