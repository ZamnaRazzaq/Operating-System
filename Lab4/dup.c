#include <stdio.h>
#include <unistd.h>

int main() {
    int fd, new_fd;

    // Open a file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Duplicate the file descriptor
    new_fd = dup(fd);
    if (new_fd == -1) {
        perror("dup");
        close(fd);
        return 1;
    }

    // Close the original file descriptor
    close(fd);

    // Now, both 'fd' and 'new_fd' point to the same file
    // You can read from 'fd' and 'new_fd' independently

    char buffer[50];
    ssize_t bytes_read;

    bytes_read = read(new_fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        close(new_fd);
        return 1;
    }

    // Close the duplicated file descriptor
    close(new_fd);

    // Print the content read from the file
    write(STDOUT_FILENO, buffer, bytes_read);

    return 0;
}
