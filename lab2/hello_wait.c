#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("Hello world\n");
	getc(stdin);

	return 0;
}
/*Step1: compile and execute
 * gcc -o hello_wait hello_wait.c
 * ./hello_wait
 *Step2: Retrieve process PID and its associated/proc folder
 * ps auxf | grep hello
 * ls /proc/<pid>
 *
 * ps : display all the information about the currently running processes.
 * 	a: show processes for all usesers
 * 	u: display the processes' user/owner info
 * 	f: display a full formal listing
 * grep hello: search for hello
 * using a pipe | to filter the necessary information
 *
*/
