#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// Similar to ex2, this time executes "wc" commmand
int main(){
    int in = open("/etc/passwd", O_RDONLY);
    int out = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0660);
    int err = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0660);
    pid_t pid = fork();
    if(!pid){
        dup2(in,0); close(in);
        dup2(out,1); close(out);
        dup2(err,2); close(err);

        execlp("wc", "wc", NULL);
        
        perror("couldn't execute");
        _exit(-1);    
    }
    return 0;
}