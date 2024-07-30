#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>
#include<fcntl.h>
const int size= 20;
key_t key = 5678;

int main(int argc, char* argv[]) {
    char totalchar[20];
    int openinfile = open(argv[1], O_RDONLY);
    ssize_t openread= read(openinfile, &totalchar, 20);
    int shmid = shmget(key,size, 0666 | IPC_CREAT);
    char* sharedMemory = (char*)shmat(shmid, nullptr, 0);
    sem_t* semaphore = sem_open("/my_semaphore", O_CREAT, 0666, 1);
 
    while ((openread) != 0){
        sem_wait(semaphore);
        strncpy(sharedMemory, totalchar, size);
        sem_post(semaphore);
    }

    *sharedMemory = '$';
    sem_close(semaphore);
    return 0;
}