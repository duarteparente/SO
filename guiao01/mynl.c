#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>


/*****************************************************************************
* Attempts to read a line from file descriptor, returns number of bytes read.
* (First Version -> Reads 1 byte at a time) 
******************************************************************************/
ssize_t readln(int fd, char* line, size_t size) {
    ssize_t count_bytes = 0;
    while(count_bytes < size - 1) {
        ssize_t bytes_read = read(fd, &line[count_bytes], 1);
        if (bytes_read < 1 || line[count_bytes++] == '\n') break;
    }
    line[count_bytes] = 0;
    return count_bytes;
}



/*******************************************************************
NAME
        mynl - number lines of file

SYNOPSIS
        mynl [FILE] [SIZE]

DESCRIPTION
        Write FILE to standard output, with line numbers added.

        With no FILE, or when FILE is -, read standard input.

        SIZE      estabilish buffer size, 1024b by default        
********************************************************************/
int main(int argc, char *argv[]){
    ssize_t bytes;
    int buf_size = 1024;
    if(argc == 3) buf_size = atoi(argv[2]);
    char *buffer = malloc(buf_size);
    int fd, counter = 1, flag = 1;
    fd = (argc < 2) ? 0 : open(argv[1], O_RDONLY);
    if (fd == -1){
        printf("%s: file not found\n", argv[1]);
        exit(-1);
    }
    char line_number[20]; 
    while((bytes = readln(fd,buffer,buf_size)) > 0){
        if (flag){
            sprintf(line_number,"     %d  ", counter++);
            write(1,line_number,strlen(line_number));
            flag = 0;
        }
        if (buffer[bytes-1] == '\n') flag = 1;
        write(1,buffer,bytes);
    }
    close(fd);
    free(buffer);
    return 0;
}