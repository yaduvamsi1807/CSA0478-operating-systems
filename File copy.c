#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int source_fd, dest_fd;
    char buffer[1024];
    ssize_t bytes_read;

    // Open the source file in read-only mode
    source_fd = open("source_file.txt", O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(1);
    }

    // Create or open the destination file in write mode
    dest_fd = open("destination_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd); 
        exit(1);
    }

    // Read data from the source file and write it to the destination file
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            exit(1);
        }
    }

    // Check for errors during reading
    if (bytes_read == -1) {
        perror("Error reading from source file");
        close(source_fd);
        close(dest_fd);
        exit(1);
    }

    // Close the file descriptors
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully!\n");

    return 0;
}
