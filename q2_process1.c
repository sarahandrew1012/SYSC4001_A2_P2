/**
 * @author Sarah Andrew, 101303468
 * @author Kaylah Mckez, 101307188
 * 
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    int counter = 0;
    int multiple = 3;
    int cycle = 0;

    if (pid < 0) {
        perror("Fork failed.");
        exit(1);
    }


    if (pid == 0) {
        // launching process 2
        char *args[] = {"./q2_process2", NULL};
        execvp("./q2_process2", args);
        perror("execvp failed.");
        exit(1);
    } else {
        // checking to see if its a multiple of 3.
        while(1) {
            if (counter % multiple == 0) {
                printf("Process 1 with (PID %d): Cycle %d - %d is a multiple of %d\n", getpid(), cycle, counter, multiple);
            } else {
                printf("Process 1 with (PID %d): Cycle %d - %d\n", getpid(), cycle, counter);
            }
            cycle++;
            counter++;
            usleep(70000);
        }
    }
    return 0;
}