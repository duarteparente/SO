#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// Execute 'ls -l' command via child process
int main(){
    pid_t pid = fork();
    if(!pid){
        execlp("ls", "ls", "-l", NULL);
        _exit(1);
    }
    int status;
    wait(&status);
    if(!WIFEXITED(status) || WEXITSTATUS(status) == 1){
        printf("fatal: couldn't execute command\n");
        _exit(-1);
    }
    return 0;
}