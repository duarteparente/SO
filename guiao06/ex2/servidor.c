#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
    if (mkfifo("fifo", 0666) < 0) {
        perror("fifo");
        _exit(-1);
    }

    char buffer[1024];
    int f = open("fifo", O_RDONLY);
    int fd = open("log", O_CREAT | O_WRONLY | O_TRUNC, 0666), bytes;

    while( (bytes = read(f,buffer,1024)) > 0){
        write(fd, buffer, bytes);
    }

    close(fd);
    unlink("fifo");
    return 0;
}