#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>


typedef struct information {
    char name[60];
    int age;
} Person;


/*****************************************************************************
OPTIONS
 -i name age       Add person record to file (returns new record's position)
 -u name age       Updates the age of the record with given name
 -o position age   Updates the age of the record in given position
******************************************************************************/
int main(int argc, char *argv[]){
    if (argc != 4){
        printf("%s: not enough arguments\n", argv[0]);
        exit(-1);
    }
    int fd, control, pos;
    Person person;
    char option = *(argv[1]+1);
    switch(option){
        case 'i':
            fd = open("????",O_APPEND);
            if (fd == -1){
                printf("%s: file not found\n", argv[1]);
                exit(-1);
            }
            strcpy(argv[2], person.name);
            person.age = atoi(argv[3]);
            control = write(fd,&person,sizeof(Person));
            if (control <= 0){
                printf("%s %d: couldn't write to file\n", argv[2], argv[3]);
                exit(-1);
            }
            off_t file_size = lseek(fd,(size_t)0,SEEK_END); // gets file size
            pos = file_size/sizeof(Person); // gets number of registers
            printf("registo %d\n", pos);
            close(fd);
            break;
        case 'u':
            fd = open("????", O_RDWR);
            if (fd == -1){
                printf("%s: file not found\n", argv[1]);
                exit(-1);
            }
            while(read(fd, &person, sizeof(Person)) > 0){
                if (!strcmp(person.name,argv[2])){
                    person.age = atoi(argv[3]);
                    lseek(fd,-(sizeof(Person)),SEEK_CUR); // repositions file offset 1 record back
                    control = write(fd,&person,sizeof(Person));
                    if (control <= 0){
                        printf("%s %d: couldn't write to file\n", argv[2], argv[3]);
                        exit(-1);
                    }
                }
            }
            close(fd);
            break;
        case 'o':
            fd = open("????", O_RDWR);
            if (fd == -1){
                printf("%s: file not found\n", argv[1]);
                exit(-1);
            }
            pos = atoi(argv[2]);
            for (int counter = 0; counter < pos; counter++)
                read(fd, &person, sizeof(Person));
            person.age = atoi(argv[3]);
            lseek(fd,-(sizeof(Person)),SEEK_CUR);
            control = write(fd,&person,sizeof(Person));
            if (control <= 0){
                printf("%s %d: couldn't write to file\n", argv[2], argv[3]);
                exit(-1);
            }
            close(fd);
            break;
        default: printf("%c: option does not exist", option); exit(-1);
    }
    return 0;
}