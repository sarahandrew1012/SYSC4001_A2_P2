/**
 * @author Sarah Andrew, 101303468
 * @author Kaylah McKesey, 101307188
 * 
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
        char *args[] = {"./q3_process2", NULL};
        execvp("./q3_process2", args);
        perror("execvp failed.");
        exit(1);
    } else {
        int index;

        while (1) {
            // call wait system call
            pid_t completed = waitpid(pid, &index, WNOHANG);
           
            if (completed == pid) {
                break;
            }
            // checks if multiple of 3
            if (counter % multiple == 0) {
                printf("Process 1  with (PID %d): Cycle %d - %d is a multiple of %d\n", getpid(), cycle, counter, multiple);
            } else {
                printf("Process with (PID %d): Cycle %d - Counter %d\n", getpid(), cycle, counter);
            }

            counter++;
            cycle++;
            usleep(70000);
        }
        // displays the process 1 PID and when process 2 finishes.
        printf("Process 1 with (PID %d): Process 2 finishes, and exits process.\n", getpid());
    }
    return 0;
}