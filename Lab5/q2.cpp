#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;
int main(int argc, char* argv[]) {
    key_t key = 5678;
    char* totalchar = nullptr;
    int filesize;
    char* temp = nullptr;
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        cout << "Fork failed" << endl;    //fork failed
    } 
    else if (pid == 0) {
        cout << "In child Process" << endl;
        int openfile = open(argv[1], O_RDONLY);  //opening the file to read the content
        filesize = lseek(openfile, 0, SEEK_END); // using lseek function to get the size of file
        lseek(openfile, 0, SEEK_SET);
        totalchar = new char[filesize];
        ssize_t openread = read(openfile, totalchar, filesize);

        int shmid = shmget(key, filesize, 0666 | IPC_CREAT);   //creating a shared memory segment
        char* charr = (char*)shmat(shmid, NULL, 0);  //mapping shared memory on the process
        memcpy(charr, totalchar, filesize);
        shmdt(charr);
        shmid = shmget(key, strlen(temp), 0666 | IPC_CREAT);
        char* newmsg = (char*)shmat(shmid, NULL, 0);


        int outfile = open(argv[1], O_WRONLY);
        write(outfile, newmsg, strlen(newmsg)); //writing the updated content in file
        close(outfile);
    } else if (pid>0) {
        wait(NULL);
        cout << "In parent process" << endl;
        int shmid = shmget(key, filesize, 0666 | IPC_CREAT);
        char* charr = (char*)shmat(shmid, NULL, 0);
        ssize_t bytesRead = strlen(charr);

        temp = new char[bytesRead];
        strcpy(temp, charr);

        for (int i = 0; i < bytesRead; i++) {      //for removing digits
            if (isalpha(charr[i])) {
                temp[i] = charr[i];
            }
        }

        for (int i = 0; i < bytesRead; i++) {       // for converting uppercase to lowercase and vice versa.
            if (temp[i] >= 'A' && temp[i] <= 'Z') {
                temp[i] += 32;
            } else if (temp[i] >= 'a' && temp[i] <= 'z') {
                temp[i] -= 32;
            }
        }

        shmid = shmget(key, strlen(temp), 0666 | IPC_CREAT);
        char* msg = (char*)shmat(shmid, NULL, 0);
        strcpy(msg, temp);

        shmdt(charr);
    }
    return 0;
}

