#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int mySystem(char *command){
    char *args[10];
    char *token;
    int index = 0;
    token = strtok(command, " \n");
    while (token != NULL) {
        if (strcmp(token, " ") && strcmp(token, "\n")){
            args[index++] = token;
            token = strtok(NULL, " \n");
        }
    }
    args[index] = NULL;
    pid_t pid = fork();
    if (pid == -1) _exit(-1);
    if(!pid){
        int result = execvp(args[0],args);
        _exit(result);
    }
    int status;
    wait(&status);
    if(!WIFEXITED(status)) _exit(2);
    return status;
}

int main(){
    int index = 0;
    char *buffer = malloc(2048);
    char *args[50];
    read(0, buffer, 2048);
    char *token;
    while((token = strsep(&buffer,"|"))){
        args[index++] = token;
    }
    int pipefd[index-1][2];
    
    for(int i=0; i<index; i++){
        if (pipe(pipefd[i]) == -1) {
            perror("error creating pipe");
            _exit(-1);
        }
    }
    pid_t pid; int i=0;
    for ( ; i < index; i++) {
        pid = fork();
        if (!pid) {
            if (i > 0)  dup2(pipefd[i-1][0],0);
            if (i != index-1) dup2(pipefd[i][1],1);
            break;
        }
    }
    for (int p = 0; p < index; p++) {
        close(pipefd[p][1]);
        close(pipefd[p][0]);
    }
    if (!pid) {
        system(args[i]);
        _exit(1);
    } 
    else {
       for (int j = 0; j < index; j++) wait(NULL); 
    }
    return 0;
}