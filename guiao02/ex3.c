#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


// Creates 10 child processes that execute sequentially
int main(){
    for(int i=0; i<10; i++){
        pid_t pid = fork();
        if (!pid){
            printf("----------- CHILD %d ----------\n", i+1);
            printf("My PID: %d\nMy Father's PID: %d\n",(int)getpid(),(int)getppid());
            _exit(i+1);
        }
        int status;
        wait(&status);
        if (WIFEXITED(status))
            printf("Exit order: %d\n",WEXITSTATUS(status));
    }

    return 0;
}