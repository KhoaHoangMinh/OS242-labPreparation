#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_KEY 0x123

/*
 * Run the two following processes in two terminals. 
 * At the writer process, you can type an input string and
observe returns from the reader process.
 */

int main(int argc, char *argv[]) {
    int shmid;
    char *shm;
    /* Shared memory segment creation */
    shmid = shmget(SHM_KEY, 1000, 0644 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    } else {
        printf("shared memory ID: %d\n", shmid);
    }

    shm = (char *) shmat(shmid, 0, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("shared memory mm: %p\n", shm);

    if (shm != 0) {
        printf("shared memory content: %s\n", shm);
    }

    sleep(10);

    if (shmdt(shm) == -1) {
        perror("shmdt");
        return 1;
    }

    return 0;
}
