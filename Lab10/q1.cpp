#include <iostream>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;
int main(int argc, char* argv[]) {
    key_t key = 5678;
    const int buffer = 1024;
    int shmid = shmget(key,buffer* sizeof(int), IPC_CREAT | 0666);
    int* data = (int*)shmat(shmid, NULL, 0);

   
    sem_t sem;
    sem_init(&sem, 1, 1); 

    pid_t pid1;
    pid1 = fork();

    if (pid1 == 0) {
        int file = open(argv[1], O_RDONLY);
        int num;
        int count = 0;

        while (read(file, &num, sizeof(int)) > 0 && count < buffer) {
            data[count++] = num;
        }

        close(file);
        shmdt(data);
        exit(0);
    } else {
        wait(NULL); 
    }

    pid_t pid2;
    pid2= fork();

    if (pid2 == 0) {
        sem_wait(&sem);

        int uniquenums[buffer];
        int size = 0;

        for (int i = 0; i < buffer; ++i) {
            int current = data[i];
            bool duplicate = false;

            for (int j = 0; j < size; ++j) {
                if (uniquenums[j] == current) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                uniquenums[size++] = current;
            }
        }

        for (int i = 0; i < size; ++i) {
            data[i] = uniquenums[i];
        }

        sem_post(&sem);
        shmdt(data);
        exit(0);
    } else {
        wait(NULL); 
    }

    sem_wait(&sem);
    int file = open(argv[1], O_WRONLY);

    for (int i = 0; i < buffer && data[i] != 0; i++) {
        write(file, &data[i], sizeof(int));
    }

    close(file);
    sem_post(&sem);
    sem_destroy(&sem);
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
