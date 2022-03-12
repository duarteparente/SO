#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/***************************************************************************
./exe [rows] [collumns] [number]

Prints the number of lines that countain the number (in ascending order)
****************************************************************************/
int main(int argc, char *argv[]){
    srand(time(NULL));
    int number, rows, colls, status;
    
    if (argc != 4){
        number = rand() % 50000;
        rows = 10;
        colls = 100000;
    }
    else {
        rows = atoi(argv[1]);
        colls = atoi(argv[2]);
        number = atoi(argv[3]);
    }

    int mat[rows][colls];
    for(int i=0; i<rows; i++)
        for(int j=0; j<colls; j++)
            mat[i][j] = rand() % 50000;
    pid_t children[rows];
    for(int i=0; i<rows; i++){
        pid_t pid = fork();
        if(!pid){
            for(int j=0; j<colls; j++)
                if (mat[i][j] == number) _exit(2);
            _exit(1);
        }
        else children[i] = pid;
    }
    for(int i=0; i<rows; i++){
        pid_t pid = waitpid(children[i],&status,0);
        if (pid == children[i] && WIFEXITED(status)){
            if (WEXITSTATUS(status) == 2) printf("Element found in line '%d'\n", i+1);
        }
        else printf("error\n");
    }
    return 0;
}