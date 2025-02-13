#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*
 * This program demonstrates inter-process communication using a pipe.
 * A parent process creates a child and sends it a message through
 * a pipe. The child receives and prints the message before exiting.
 */

int main() {
    int fd[2];  // fd[0] read - fd[1] write
    pid_t pid;
    char msg[] = "Hello from Parent!!";
    char buffer[100];

    if(pipe(fd) < 0) {
        perror("pipe failed :(");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if(pid < 0) {
        perror("fork failed :(");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {  // Child process
        printf("Child: PID = %d, waiting for message...\n", getpid());
        close(fd[1]);  // Close write end

        read(fd[0], buffer, sizeof(buffer));
        printf("Child: Received message: %s\n", buffer);

        close(fd[0]);  // Close read end
        exit(EXIT_SUCCESS);
    }
    else {  // Parent process
        printf("Parent: Created child with PID = %d\n", pid);
        close(fd[0]);  // Close read end

        write(fd[1], msg, strlen(msg) + 1);
        printf("Parent: Sent message to child\n");

        close(fd[1]);  // Close write end
        wait(NULL);    // Wait for child to exit

        printf("Parent: Child has exited.\n");
    }

    return 0;
}
