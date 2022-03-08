#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


// Creates a child process, with both havinf different instructions
int main(){
    pid_t pid = fork();
    if (!pid){
        puts("----------- CHILD ----------");
        printf("My PID: %d\nMy Father's PID: %d\n",(int)getpid(),(int)getppid());
    }
    else {
        puts("---------- FATHER ----------");
        printf("My PID: %d\nMy Father's PID: %d\nMy Son's PID: %d\n",(int)getpid(),(int)getppid(),(int)pid);
    }
    return 0;
}