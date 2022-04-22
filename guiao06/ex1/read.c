#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char buffer[1024];
    int fd = open("fifo", O_RDONLY), bytes;

    while( (bytes = read(fd,buffer,1024)) > 0 ){
        write(1, buffer, bytes);
    }

    unlink("fifo");

    return 0;
}