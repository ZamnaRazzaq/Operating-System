#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring> 
using namespace std;

int main() {
    const char* pipeName = "mypipe";
    mkfifo(pipeName, 0666);
    int fd1 = open(pipeName, O_WRONLY);
    const char* data = "* 4 10\n";

    write(fd1, data, strlen(data));

    close(fd1);
    int fd = open(pipeName, O_RDONLY);
    int result;
    ssize_t bytesread = read(fd, &result, sizeof(result));

    close(fd);

    cout << "Result received from the server: " << result << endl;

    return 0;
}

