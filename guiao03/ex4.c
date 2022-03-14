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


int main(){
    char commands[1024];
    fgets(commands, 1024, stdin);
    int last_index = strcspn(commands, "\n");
    commands[last_index] = '\0';
    int result = mySystem(commands);
    switch(result){
        case -1: printf("could not create child process\n"); _exit(-1);
        case 2: printf("command could not be executed\n"); _exit(-1);
        default: break;
    }
    return 0;
}