/**
 * @author Sarah Andrew, 101303468
 * @author Kaylah Mckez, 101307188
 * 
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok(".", 'S');
    // define sharing variables
    int shmid = shmget(key, sizeof(int) * 2, IPC_CREAT | 0666);
    int *shm_ptr = (int *)shmat(shmid, NULL, 0);

    // defining shared memory vars.
    int *multiple = &shm_ptr[0];
    int *shared_vars = &shm_ptr[1];
    int cycle = 0;

    // waits for process 1 counter to exceed 100.
    while (*shared_vars <= 100) {
        usleep(70000);
    }

    while (*shared_vars <= 500) {
        if (*shared_vars % *multiple == 0) {
            printf("Process 2 with (PID %d): Cycle %d - %d is a multiple of %d\n", getpid(), cycle, *shared_vars, *multiple);
        } else {
            printf("Process 2 with (PID %d): Cycle %d - Counter %d\n", getpid(), cycle, *shared_vars);
        }
        // time to slow output
        cycle++;
        usleep(70000);

    }
    printf("Process 2 with (PID %d): Exiting with %d.\n", getpid(), *shared_vars);
    // detacth memory
    shmdt(shm_ptr);
    return 0;
}