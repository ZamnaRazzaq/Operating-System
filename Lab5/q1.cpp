#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

int main() {
    key_t key = 5678;  // Key associated with shared memory segment
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        cout << "Fork failed" << endl;  // Fork failed
    } else if (pid == 0) {
        cout << "In child Process" << endl;
        int shmid = shmget(key, sizeof(int) * 5, 0666 | IPC_CREAT);  // To allocate shared memory
        int* data = (int*)shmat(shmid, NULL, 0);                 // Map shared memory to child process in data variable
        cout << "Enter the data to square : ";
        for (int i = 0; i < 5; i++) {
            cin >> data[i];  // Integers to square
        }
        cout << endl;
    } else if (pid > 0) {
        wait(NULL);
        cout << "In parent process" << endl;
        int shmid = shmget(key, sizeof(int) * 5, 0666 | IPC_CREAT);
        int* data = (int*)shmat(shmid, NULL, 0);
        int* temp = data;
        cout << "Square of the given numbers : ";
        for (int i = 0; i < 5; i++) {
            int square = temp[i] * temp[i];  // Convert to square and then print
            cout << square << " ";
        }
        cout << endl;
    }
    return 0;
}
