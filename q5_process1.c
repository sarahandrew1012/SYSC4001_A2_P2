/**
 * @author Sarah Andrew, 101303468
 * @author Kaylah McKesey, 101307188
 * 
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main() {
    pid_t pid = fork();
    int counter = 0;
    int cycle = 0;
    key_t key = ftok(".", 'S');
    key_t key_sem = ftok(".", 'M');
    int status;

    int shmid = shmget(key, sizeof(int) * 2, IPC_CREAT | 0666);
    int *shm_ptr = (int *)shmat(shmid, NULL, 0);
    int semid = semget(key_sem, 1, 0666 | IPC_CREAT);

    // shared memory variables
    int *multiple = &shm_ptr[0];
    int *shared_vars = &shm_ptr[1];
    *multiple = 3; 
    *shared_vars = 0;


    // set it to unlocked
    semctl(semid, 0, SETVAL, 1);

    // process for wait & lock and also signal & unlock
    struct sembuf lock  = {0, -1, 0};
    struct sembuf unlock = {0, 1, 0};

    if (pid < 0) {
        perror("Fork failed.");
        exit(1);
    }

    if (pid == 0) {
        // launching process 2
        char *args[] = {"./q5_process2", NULL};
        execvp("./q5_process2", args);
        perror("execvp failed.");
        exit(1);
    } else {
        while (*shared_vars <= 500) {
            // protect share memory
            semop(semid, &lock, 1);

            if (*shared_vars > 100) {
                // uses shared variable to determine the multiple of 3 & displays it
                if (*shared_vars % *multiple == 0) {
                printf("Process 1 with (PID %d): Cycle number: %d - %d is a multiple of %d.\n", getpid(), cycle, *shared_vars, *multiple);
            } else {
                printf("Process 1 with (PID %d): Cycle number: %d - Counter: %d\n", getpid(), cycle, *shared_vars);
            }
        }
            (*shared_vars)++;
            cycle++;
            semop(semid, &unlock, 1);
            usleep(70000);
        }
        waitpid(pid, &status, 0);
        // clean up processes
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, 0);
        semctl(semid, 0, IPC_RMID);
    }
    return 0;
}