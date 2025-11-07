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
    int counter = 0;
    int cycle = 0;
    int multiple = 3;

    // checking to see if its a multiple of 3
    for (; counter >= -500; counter--, cycle++) {
        if (counter % multiple == 0) {
            printf("Process 2 with (PID %d): Cycle %d - %d is a multiple of %d\n", getpid(), cycle, counter, multiple);
        } else {
            printf("Process 2 with (PID %d): Cycle %d - Counter %d\n", getpid(), cycle, counter);
        }
        // time to slow output
        usleep(70000);
    }
    printf("Process 2 with (PID %d): Exiting with %d.\n", getpid(), counter);
    return 0;
}