#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

/*
 * This program demonstrates file writing from two processes.
 * Both parent and child write their PIDs to the same file.
 * File locking is used to prevent race conditions during writing.
 * 
 * Note: We always append new data to the file. To erase old data, 
 *       we could clear the file before fork(), but we chose to preserve 
 *       all prints.
 */

void write_pid_to_file(const char *filename, const char *tag) {
    struct flock lock;
    char buffer[100];
    int fd;

    // Open file with read and write permissions
    fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if(fd < 0) {
        perror("open file failed");
        exit(EXIT_FAILURE);
    }

    // Prepare lock structure
    memset(&lock, 0, sizeof(lock));
    lock.l_type   = F_WRLCK;  // Write lock
    lock.l_whence = SEEK_SET;
    lock.l_start  = 0;
    lock.l_len    = 0;        // Lock whole file

    // Get write lock
    if(fcntl(fd, F_SETLKW, &lock) < 0) {
        perror("fcntl failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write to file
    snprintf(buffer, sizeof(buffer), "%s PID: %d\n", tag, getpid());
    if( write(fd, buffer, strlen(buffer)) < 0 ) {
        perror("write failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Release lock
    lock.l_type = F_UNLCK;
    if( fcntl(fd, F_SETLK, &lock) < 0 ) {
        perror("fcntl unlock failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main() {
    pid_t pid;
    const char *filename = "pids_file.txt";

    pid = fork();

    if(pid < 0) {
        perror("fork failed :(");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {  // Child process
        write_pid_to_file(filename, "Child");
        exit(EXIT_SUCCESS);
    }
    else {  // Parent process
        write_pid_to_file(filename, "Parent");
        wait(NULL);  // Wait for child to exit
    }

    return 0;
}
