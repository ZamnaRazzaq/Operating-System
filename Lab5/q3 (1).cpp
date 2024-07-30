#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
using namespace std;
int main() {
    pid_t pid;
    int fd1[2], fd2[2];   
    pipe(fd1);  //creating two pipes for communication
    pipe(fd2);
    pid = fork();

    if (pid < 0) {
        cout<<"Fork failed";
    }
    if (pid == 0) {
        close(fd1[1]); 
        cout << "In child process" << endl;

        char recievemsg[100];
        ssize_t bytesRead = read(fd1[0], recievemsg, sizeof(recievemsg));  //reading the string message from parent process

        for (int i = 0; i < bytesRead; i++) {    //converting uppercase to lowercase and vice versa
            if (recievemsg[i] >= 'A' && recievemsg[i] <= 'Z') {
                recievemsg[i] += 32;
            } else if (recievemsg[i] >= 'a' && recievemsg[i] <= 'z') {
                recievemsg[i] -= 32;
            }
        }

        close(fd1[0]); 

        close(fd2[0]); 
        write(fd2[1], recievemsg, bytesRead);   //using pipe2 and writing the updated message in it and passing it to parent
        close(fd2[1]); 

    } else {
        cout << "In parent process" << endl;
        char msg[100];
        cout << "Enter a string: ";
        cin.getline(msg, sizeof(msg));

        close(fd1[0]); 
        write(fd1[1], msg, strlen(msg)); //writing the message taken from user and passing it to child for conversion
        close(fd1[1]); 

        close(fd2[1]); 
        char newmessage[100];
        read(fd2[0], newmessage, sizeof(newmessage)); //reading the updated message from user
        close(fd2[0]);


        cout << "The new message is: " << newmessage << endl;
    }

    return 0;
}

