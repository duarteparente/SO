#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
 * Execute a shell command
 */
int mySystem(char *commands){
    int index = 0;
    char *args[1024];
    char *token;
    while((token = strsep(&commands," "))){
        args[index++] = strdup(token);
    }
    args[index] = NULL;
    pid_t pid = fork();
    if (pid == -1) _exit(-1);
    if(!pid){
        execvp(args[0],args);
        _exit(1);
    }
    int status;
    wait(&status);
    if(!WIFEXITED(status) || WEXITSTATUS(status) == 1) _exit(2);
    return 0;
}