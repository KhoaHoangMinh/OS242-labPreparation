#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int snd(const char *fifo_path, const char *message) {
    // Open the FIFO for writing
    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for writing");
        return -1;
    }

    // Write the message to the FIFO
    ssize_t bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) {
        perror("Failed to write to FIFO");
        close(fd);
        return -1;
    }

    printf("Sent message: %s\n", message);

    // Close the FIFO
    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fifo_name> <message>\n", argv[0]);
        return 1;
    }

    const char *fifo_path = argv[1];  // FIFO path passed as argument
    const char *message = argv[2];    // Message passed as argument

    snd(fifo_path, message);  // Send the message
    return 0;
}

