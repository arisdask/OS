#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

/*
 * This program demonstrates inter-process communication using signals.
 * A parent process creates a child and signals it using SIGUSR1.
 * The child catches the signal, prints a message, and exits.
 */

// Signal handler for child process
void signal_handler(int sig) {
    printf("Child: Received signal %d from parent\n", sig);
}

int main() {
    pid_t pid;

    pid = fork();

    if(pid < 0) {
        perror("fork failed :(");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {  // Child process
        printf("Child: PID = %d, waiting for signal...\n", getpid());
        
        if(signal(SIGUSR1, signal_handler) == SIG_ERR) {
            perror("signal");
            exit(EXIT_FAILURE);
        }

        pause();  // Wait for signal
        exit(EXIT_SUCCESS);
    }
    else {  // Parent process
        printf("Parent: Created child with PID = %d\n", pid);
        
        sleep(2);
        
        printf("Parent: Sending signal to child\n");
        if(kill(pid, SIGUSR1) < 0) {
            perror("kill");
            exit(EXIT_FAILURE);
        }

        wait(NULL);  // Wait for child to exit
        printf("Parent: Child has exited.\n");
    }

    return 0;
}
