#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


// Simulate bash command 'ls /etc | wc -l'
int main(){
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("error creating pipe");
        _exit(-1);
    }
    pid_t pid = fork();
    if(!pid){
        close(pipefd[1]);
        dup2(pipefd[0],0);
        execlp("wc", "wc", "-l", NULL);
        _exit(0);
    }
    close(pipefd[0]);
    dup2(pipefd[1], 1);
    execlp("ls", "ls", "/etc", NULL);
    close(pipefd[1]);

    return 0;
}