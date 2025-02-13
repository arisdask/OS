#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3  // Number of child processes to create

/*
 * This program demonstrates process creation using a loop-based approach
 * rather than sequential fork() calls. While sequential calls like:
 *   fork();
 *   fork();
 *   fork();
 * would create 2^3 = 8 processes (7 new children + the initial parent),
 * our loop-based implementation creates exactly NUM_CHILDREN processes.
 * Each child process prints its PID and parent PID before terminating.
 */

int main() {
    pid_t pids[NUM_CHILDREN];

    for(int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();

        if(pids[i] < 0) {  // Fork failed :(
            perror("fork failed");
            // Clean up previously created children
            for(int j = 0; j < i; j++) {
                kill(pids[j], SIGTERM);
            }
            exit(EXIT_FAILURE);
        }
        else if(pids[i] == 0) {  // Child process
            printf("Child %d: PID = %d, Parent PID = %d\n", i+1, getpid(), getppid());
            exit(EXIT_SUCCESS);  // Child exits
        }
        else {  // Parent process
            printf("Parent: Created child %d with PID = %d\n", i+1, pids[i]);
        }
    }

    // Parent waits for all children to exit
    for(int i = 0; i < NUM_CHILDREN; i++) { wait(NULL); }

    printf("Parent: All children have exited.\n");
    return 0;
}
