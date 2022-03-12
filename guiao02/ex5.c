#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/*******************************************************************************************
./exe [rows] [collumns] [number]

Calculates # occurrences of a number in a random generated matrix using process management
*********************************************************************************************/
int main(int argc, char *argv[]){
    srand(time(NULL));
    int number, rows, colls, status, counter = 0, total = 0;
    
    if (argc != 4){
        number = rand() % 5000;
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
            mat[i][j] = rand() % 5000;

    char buf[256];
    int fd = open("temp.txt", O_RDWR | O_CREAT, 0660);
    for(int i=0; i<rows; i++){
        pid_t pid = fork();
        if(!pid){
            for(int j=0; j<colls; j++)
                if (mat[i][j] == number) counter++;
            sprintf(buf,"%d", counter);
            write(fd,buf,strlen(buf));
            lseek(fd,0,SEEK_SET);
            _exit(1);
        }
        if (wait(&status) < 0){
            puts("fatal: error waiting for child process");
            exit(-1);
        }
        read(fd,buf,256);
        lseek(fd,0,SEEK_SET);
        total += atoi(buf);
    }
    close(fd);
    remove("temp.txt");
    printf("Number '%d' was found %d times(s)\n", number, total);
    return 0;
}