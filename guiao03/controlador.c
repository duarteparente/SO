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
    while((token = strsep(&commands," \n"))){
        args[index++] = strdup(token);
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

/**
 * Execute an unlimited number of programs, until their return value = 0.
 * 
 * Programns can't have arguments.
 */
int main(int argc, char *argv[]){
    if (argc < 2) {
        perror("not enough arguments");
        _exit(-1);
    }
    int counter = 1;
    char result[100];
    for (int i = 1; i < argc; i++) {
        while (mySystem(argv[i]) != 0) counter++;
        sprintf(result, "%s %d\n", argv[i], counter);
        write(0,result,strlen(result));
    }
    return 0;
}