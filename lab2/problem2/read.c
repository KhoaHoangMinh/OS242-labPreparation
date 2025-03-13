#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int rcv(const char *fifo_path) {
    // Open the FIFO for reading
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for reading");
        return -1;
    }

    // Buffer to hold the received message
    char buffer[256];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Failed to read from FIFO");
        close(fd);
        return -1;
    }

    buffer[bytes_read] = '\0';  // Null-terminate the string
    printf("Received message: %s\n", buffer);

    // Close the FIFO
    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fifo_name>\n", argv[0]);
        return 1;
    }

    const char *fifo_path = argv[1];  // FIFO path passed as argument
    rcv(fifo_path);  // Receive the message
    return 0;
}

