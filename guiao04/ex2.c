#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

ssize_t readln(int fd, char* line, size_t size) {
    ssize_t count_bytes = 0;
    while(count_bytes < size - 1) {
        ssize_t bytes_read = read(fd, &line[count_bytes], 1);
        if (bytes_read < 1 || line[count_bytes++] == '\n') break;
    }
    line[count_bytes] = 0;
    return count_bytes;
}

// Similar to ex1, this time using a child process
int main(){
    int in = open("/etc/passwd", O_RDONLY);
    int out = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0660);
    int err = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0660);
    pid_t pid = fork();
    if(!pid){
        dup2(in,0); close(in);
        dup2(out,1); close(out);
        dup2(err,2); close(err);


        // Output testing
        ssize_t bytes;
        char buffer[1024];
        int i = 0;
        while((bytes = readln(0,buffer,1024)) > 0){
            write(1,buffer,bytes);
        }
        
        perror("erro");

        _exit(0);    
    }
    return 0;
}