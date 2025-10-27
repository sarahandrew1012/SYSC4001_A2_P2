#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    pid_t pid = fork();
    int counter = 0;
    int cycle = 0;
    int status;

    if (pid < 0) {
        perror("Fork failed.");
        exit(1);
    }

    if (pid == 0) {
        char *args[] = {"./process2", NULL};
        execvp("./process2", args);
        perror("execvp failed.");
        exit(1);
    } else {
        while (1) {
            if (counter % 3 == 0) {
                printf("Cycle number: %d - %d is a multiple of 3.\n", cycle, counter);
            } else {
                printf("Cycle number: %d\n", cycle);
            }
            counter++;
            cycle++;
            usleep(50000);
        }
    }
    return 0;
}