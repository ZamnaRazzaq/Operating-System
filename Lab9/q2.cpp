#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <cstring>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstdlib>

using namespace std;

int main() {
    key_t key = 5678;
    sem_t sem1;

    sem_init(&sem1, 1, 1);

    int sum1 = 0;
    int sum2 = 0;
    int count1 = 0;
    int count2 = 0;
    int average = 0;
    int totalsum = 0;
    int totalcount = 0;
    char charr1, charr2;
    int openfile1 = open("file1.txt", O_RDONLY);
    int openfile2 = open("file2.txt", O_RDONLY);

    ssize_t openread1, openread2;

    openread1 = read(openfile1, &charr1, 1);
    openread2 = read(openfile2, &charr2, 1);

    int shmid = shmget(key, 5 * sizeof(int), 0666 | IPC_CREAT);
    int* data = (int*)shmat(shmid, NULL, 0);

    for (int i = 0; i < 5; i++) {
        data[i] = 0;
    }

    pid_t pid;
    pid = fork();

    if (pid < 0) {
        cout << "Fork failed" << endl;
    } else if (pid == 0) {
        sem_wait(&sem1);
        cout << "In first child Process" << endl;
        while ((openread1 = read(openfile1, &charr1, 1)) > 0) {
            if (isdigit(charr1)) {
                sum1 = sum1 + (charr1 - '0');
                data[0] = sum1;
                count1++;
            }
        }
        data[1] = count1;
        sem_post(&sem1);
        shmdt(data);
        exit(0);
    } else {
        wait(NULL);

        pid_t pid1 = fork();
        if (pid1 < 0) {
            cout << "Fork  failed" << endl;
        } else if (pid1 == 0) {
            sem_wait(&sem1);
            cout << "In second child Process" << endl;
            while ((openread2 = read(openfile2, &charr2, 1)) > 0) {
                if (isdigit(charr2)) {
                    sum2 = sum2 + (charr2 - '0');
                    data[2] = sum2;
                    count2++;
                }
            }
            data[3] = count2;
            sem_post(&sem1);
            shmdt(data);
            exit(0);
        } else {
            wait(NULL);
            sem_wait(&sem1);
            totalsum = data[0] + data[2];
            totalcount = data[1] + data[3];
            average = static_cast<int>(totalsum / static_cast<float>(totalcount));
            cout << "The total sum is: " << totalsum << endl;
            cout << "The total count is: " << totalcount << endl;
            cout << "The Average is: " << average << endl;
            sem_post(&sem1);
            shmdt(data);
            shmctl(shmid, IPC_RMID, NULL);
        }
    }

    sem_destroy(&sem1);

    close(openfile1);
    close(openfile2);

    return 0;
}

