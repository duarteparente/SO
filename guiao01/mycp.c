#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>


/*******************************************************************
NAME
        mycp - copy files

SYNOPSIS
        mycp SOURCE DEST [SIZE]

DESCRIPTION
        Copy SOURCE TO DEST

        SIZE     estabilish buffer size, 1024b by default        
********************************************************************/
int main(int argc, char *argv[]){
    int buf_size = 1024;
    if(argc == 4) buf_size = atoi(argv[3]);
    if (argc < 3){
        printf("%s: not enough arguments\n", argv[0]);
        exit(-1);
    }
    int fsrc = open(argv[1], O_RDONLY);
    if (fsrc == -1){
        printf("%s: file not found\n", argv[1]);
        exit(-1);
    }
    char *buffer = malloc(buf_size);
    int fdest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0660);
    ssize_t bytes;
    while((bytes = read(fsrc,buffer,buf_size)) > 0){
        write(fdest,buffer,bytes);
    }
    close(fsrc);
    close(fdest);
    free(buffer);
    return 0;
}