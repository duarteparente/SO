#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/**************************************************************************************
* Program that executes commands passed as arguments, allowing entry/exit redirecting
*
* ./exe [-i new_stdin] [-o new_stdout] command [arg1 arg2 arg3 ....] 
***************************************************************************************/
int main(int argc, char *argv[]){
    int in, out, index = 1, i, j=0, status;

    if (!strcmp(argv[1], "-i")){
        index += 2;
        if (in = open(argv[2], O_RDONLY) < 0) _exit(-1);
        dup2(in,0); close(in); 
    }
    if (!strcmp(argv[index], "-o")) {
        if (out = open(argv[index+1], O_CREAT | O_WRONLY | O_TRUNC, 0660) <0) _exit(-1); 
        index += 2;
        dup2(out,1); close(out); 
    }

    char *args[1024];
    for(i=index; i<argc; i++, j++){
        args[j] = argv[i];
    }
    args[j] = NULL;
    
    pid_t pid = fork();
    if(!pid){
        
        execvp(args[0], args);
        _exit(-1);

    }

    wait(&status);
    return 0;
}