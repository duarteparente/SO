#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


// Gets program and its parent's PID
int main(){
    pid_t mypid = getpid();
    pid_t ppid = getppid();
    printf("My PID: %d\nMy Father's PID: %d\n",(int)mypid,(int)ppid);
    return 0;
}