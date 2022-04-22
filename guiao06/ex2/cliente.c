#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(){

    char buffer[1024];

    int fd = open("fifo", O_WRONLY), bytes;
    while( (bytes = read(0,buffer,1024)) > 0){
        write(fd, buffer, bytes);
    }

    close(fd);

    return 0;
}