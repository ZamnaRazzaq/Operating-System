#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main() {
    char operatorr;
    int operand1, operand2;
    int result;

    const char* pipeName = "mypipe";
    mkfifo(pipeName, 0666);

    int fd = open(pipeName, O_RDONLY);
    int fd1 = open(pipeName, O_WRONLY);

    char totalchar[1024];
    ssize_t bytesread = read(fd, totalchar, sizeof(totalchar));

    close(fd);

    operatorr = totalchar[0];
    sscanf(totalchar + 2, "%d %d", &operand1, &operand2);

    if (operatorr == '-') {
        result = operand1 - operand2;
    } else if (operatorr == '+') {
        result = operand1 + operand2;
    } else if (operatorr == '*') {
        result = operand1 * operand2;
    } else if (operatorr == '/') {
        if (operand2 != 0) {
            result = operand1 / operand2;
        } else {
            cerr << "Error: Division by zero" << endl;
            result = 0;
        }
    } else {
        cerr << "Invalid operator" << endl;
        result = 0;
    }
    close(fd1);

    fd1 = open(pipeName, O_WRONLY);
    write(fd1, &result, sizeof(result));
    close(fd1);

    cout << "Result sent to the client: " << result << endl;

    remove(pipeName);

    return 0;
}

