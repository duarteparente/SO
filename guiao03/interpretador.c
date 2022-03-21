#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Execute a shell command
 */
int mySystem(char *commands){
    int index = 0, backgroud = 0;
    char *args[1024];
    char *token;
    while((token = strsep(&commands," "))){
        args[index++] = strdup(token);
    }
    if (!strcmp(args[index-1],"&")) { backgroud = 1; index--; } 
    args[index] = NULL;
    pid_t pid = fork();
    if (pid == -1) _exit(-1);
    if(!pid){
        execvp(args[0],args);
        _exit(1);
    }
    if(!backgroud){
        int status;
        wait(&status);
        if(!WIFEXITED(status) || WEXITSTATUS(status) == 1) _exit(2);
    }
    return 0;
}

/**
 * Simple command interpreter, trying to simulate bash.
 * 
 * Commands can have arguments associated, and can run in background (when & is used).
 */
int main(int argc, char *argv[]){
    char commands[1024];
    read(0, commands, 1024);
    int last_index = strcspn(commands, "\n");
    commands[last_index] = '\0';
    mySystem(commands);
    return 0;
}