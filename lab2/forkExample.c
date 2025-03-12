#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int pid;

	printf("Start of main...\n");

	pid = fork();
	if(pid > 0) {
		// Parent process
		printf("Parent section...\n");
	} else if (pid == 0) {
		// Child process
		printf("\nfork created...\n");
	} else {
		// Fork creation failed
		printf("\nfork creation failed!!!\n");
	}

	return 0;
}
/*Understanding fork()
 * Parent process: (pid > 0), indicates process is the parent process. The returned value is the PID of the child process.
 * This program demonstrates how a parent process can create a child process using the fork() function. When fork() is called, two processes are created: the parent process continues from where the fork() was called, and the child process starts a new execution flow from the same point*/
