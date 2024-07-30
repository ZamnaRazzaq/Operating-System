#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstdlib>
#include<cstring>
using namespace std;
int main() {
    
    char buffer;
    int sum = 0;
    char temp[50];
    int inputfd = open("input.txt", O_RDONLY);
    if (inputfd == -1) {
        cout << "Error opening the file" << endl;
    }

    int newfd = dup(inputfd);
    if (newfd == -1) {
        cout << "dup function did not run successfully" << endl;
        close(inputfd);
    }
    int outputfd = open("output.txt", O_WRONLY );

    if (outputfd == -1) {
        cout << "Error opening the file" << endl;
    }
    int outfd = dup(outputfd);
    if (outfd == -1) {
        cout << "dup function did not run successfully" << endl;
        close(outputfd);
        close(inputfd);
    }
    while (read(newfd,&buffer,sizeof(buffer)) > 0) {
        if (isdigit(buffer)) {
            sum =sum+buffer;
        }
    }
 
    snprintf(temp, sizeof(temp), "%d", sum);
    write(outfd, temp, strlen(temp));
    close(outputfd);
    close(inputfd);

    return 0;
}
