/**
 * @author Sarah Andrew, 101303468
 * @author Kaylah McKesey, 101307188
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main() {
    // create process
    pid_t pid = fork();

    // check to make sure fork doesn't fail
    if (pid < 0) {
        perror("Fork failed.");
        exit(1);
    }
    // checks for the child process
    if (pid == 0) {
        int counter = 0;
        while (1) {
            printf("Child Process with (PID: %d): Counter = %d\n", getpid(), counter);
            counter++;
            usleep(5000);
        }

    // does the parent process
    } else {
        int counter = 0;
        while (1) {
            printf("Parent Process with (PID %d): Counter = %d\n", getpid(), counter);
            counter++;
            usleep(5000);

        }
    }
    return 0;
}