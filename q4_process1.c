/**
 * @author Sarah Andrew, 101303468
 * @author Kaylah Mckez, 101307188
 * 
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    pid_t pid = fork();

    key_t key = ftok(".", 'S');
    // declaring the shared memory space.
    int shmid = shmget(key, sizeof(int) * 2, IPC_CREAT | 0666);
    int *shm_ptr = (int *)shmat(shmid, NULL, 0);

    // making the shared variables
    int *counter = &shm_ptr[1];
    int *multiple = &shm_ptr[0];

    *multiple = 3;
    *counter = 0;

    int cycle = 0;

    if (pid < 0) {
        perror("Fork failed.");
        exit(1);
    }

    if (pid == 0) {
        // launching process 2
        char *args[] = {"./q4_process2", NULL};
        execvp("./q4_process2", args);
        perror("execvp failed.");
        exit(1);
    } else {
        while (*counter <= 500) {
            if (*counter %  *multiple == 0) {
                printf("Process 1 with (PID %d): Cycle %d - %d is a multiple of %d\n", getpid(), cycle, *counter, *multiple);
            } else  {
                printf("Process 1 with (PID %d): Cycle %d - Counter %d\n", getpid(), cycle, *counter);
            }

            (*counter)++;
            cycle++;
            usleep(70000);
        }
        // checking to see if its a multiple of 3.
        printf("Process 1 with (PID %d): Process 2 counter is 500 and exits process.\n", getpid());
        wait(NULL);

        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID,NULL);
    }  
    return 0;
}