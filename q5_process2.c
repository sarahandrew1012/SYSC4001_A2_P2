/**
 * @author Sarah Andrew, 101303468
 * @author Kaylah McKesey, 101307188
 * 
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main() {
    int cycle = 0;
    key_t key = ftok(".", 'S');
    key_t key_sem = ftok(".", 'M');

    int shmid = shmget(key, sizeof(int) * 2, IPC_CREAT | 0666);
    int *shm_ptr = (int *)shmat(shmid, NULL, 0);
    int semid = semget(key_sem, 1, 0666 | IPC_CREAT);

    // defining shared memory vars.
    int *multiple = &shm_ptr[0];
    int *shared_vars = &shm_ptr[1];

    // lock & unlock process
    struct sembuf lock = {0, -1, 0};
    struct sembuf unlock = {0, 1, 0};

    while (*shared_vars <= 100) {
        usleep(70000);
    }

    for (;*shared_vars <= 500; cycle++) {
        // lock/protect
        semop(semid, &lock, 1);
        
        // checking to see if a multiple of 3
        if (*shared_vars % *multiple == 0) {
            printf("Process 2 with (PID %d): Cycle number: %d - %d is a multiple of %d.\n", getpid(), cycle, *shared_vars, *multiple);
        } else {
            printf("Process 2 with (PID %d):  Cycle number: %d - Counter: %d\n", getpid(), cycle, *shared_vars);
        }
        // to slow down the output & unlock
        semop(semid, &unlock, 1);
        usleep(700000);
    }
    printf("Process 2 with (PID %d): Exiting with %d.\n", getpid(), *shared_vars);
    // detach memory
    shmdt(shm_ptr);
    return 0;
}