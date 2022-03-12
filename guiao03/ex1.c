#include <unistd.h>
#include <stdio.h>

// Execute 'ls -l' command
int main(){
    execlp("ls", "ls", "-l", NULL);
    
    // if the command doesn't fail this is never executed
    printf("fatal: couldn't execute command\n");
    _exit(-1);
    return 0;
}