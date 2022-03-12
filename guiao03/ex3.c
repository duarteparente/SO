#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// Execute a list of commands in concurrency
int main(int argc, char *argv[]){
    int status;
    for(int i=1; i<argc; i++){
        pid_t pid = fork();
        if(!pid){
            execlp(argv[i],argv[i],NULL);
            _exit(1);
        }
    }
    for(int i=0; i<argc; i++){
        pid_t pid = wait(&status);
        if(!WIFEXITED(status) || WEXITSTATUS(status) == 1){
            printf("fatal: couldn't execute command\n");
            _exit(-1);
        }
    }
    return 0;
}