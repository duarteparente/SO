#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/*********************************************************************************
* Creates an anonymous pipe and a child process.
* Father sends the string given as exec argument to be read by the child.
*
* ./exe StringToBeRead
**********************************************************************************/
int main(int argc, char *argv[]){
    char buffer[1024];
    int status, bytes_read;
    if(argc < 2){
        perror("not enough arguments");
        _exit(-1);
    }
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("error creating pipe");
        _exit(-1);
    }
    pid_t pid = fork();
    if (!pid){
        close(pipefd[1]);
        bytes_read = read(pipefd[0], buffer, 1024);
        write(1, buffer, bytes_read);
        write(1,"\n",1);
        _exit(0);
    }
    close(pipefd[0]);
    write(pipefd[1], argv[1], strlen(argv[1]));
    close(pipefd[1]);
    wait(NULL);
    return 0;
}