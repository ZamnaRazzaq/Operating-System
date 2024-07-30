#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include<iostream>
using namespace std;
key_t key = 5678;

void waitForEnterKey() {
    cout << "Press Enter to continue";
    char enter;
    cin.get(enter);
}

int main() {
    int shmid = shmget(key, 20, 0666 | IPC_CREAT);
    char* sharedMemory = (char*)shmat(shmid, nullptr, 0);
    sem_t* semaphore = sem_open("/my_semaphore", O_CREAT, 0666, 1);

    while (*sharedMemory != '$') {
        sem_wait(semaphore);
        write(1, sharedMemory, 20);  
        cout << endl;

        waitForEnterKey();
        sem_post(semaphore);  
    }
    shmdt(sharedMemory);
    return 0;
}