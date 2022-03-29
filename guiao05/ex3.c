#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


/*********************************************************************************
* Father sends the string given via user input. That input serves as stdin for 
* child at 'wc' command execution.
*
* ./exe [number of input lines]
**********************************************************************************/
int main(int argc, char *argv[]){
    int index = 1;
    if(argc == 2) index = atoi(argv[1]);
    char buffer[1024];
    char *lines[index];
    for(int i=0; i<index; i++){
        read(0, buffer, 1024);
        int last_index = strcspn(buffer, "\n");
        buffer[last_index] = '\0';
        lines[i] = buffer;
    }
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("error creating pipe");
        _exit(-1);
    }
    pid_t pid = fork();
    if(!pid){
        close(pipefd[1]);
        dup2(pipefd[0],0);
        execlp("wc", "wc", NULL);
        _exit(0);
    }
    close(pipefd[0]);
    for(int i=0; i<index; i++){
        write(pipefd[1], lines[i], strlen(lines[i]));
    }
    close(pipefd[1]);
    wait(NULL);
    return 0;
}