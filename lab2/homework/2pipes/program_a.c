#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_TO_B "fifo_to_B"
#define FIFO_TO_A "fifo_to_A"

typedef struct {
	int id;
	int active;
	pthread_t t_id;
	//pthread_mutex_t lock;
} ThreadInfo;

int count=0;
ThreadInfo threadArray[100];

void* worker_thread(void* arg){	
	pthread_detach(pthread_self());
	printf("Counting to 1000...\n");
	for (int i=0; i < 1000; i++) sleep(1);
	return NULL;
}

void create_thread(){
	//pthread_mutex_lock (&manager.lock);
	pthread_create(&threadArray[count].t_id, NULL, worker_thread, NULL);
	threadArray[count].id = count;
	threadArray[count].active = 1;
	count++;
	//pthread_mutex_unlock (&manager.lock);
}

void list_threads(){
	//pthread_mutex_lock (&manager.lock);
	printf("Active Threads of A:\n");
	fflush(stdout);
	for (int i = 0; i < count; i++){
		if (threadArray[i].active != 0){
			printf("%d ", i);
			fflush(stdout);
		}
	}
	printf("\n");
	fflush(stdout);
	//pthread_mutex_unlock (&manager.lock);
}

void kill_thread (int id){
	//pthread_mutex_lock (&manager.lock);
	if (id >= 0 && id < count){
		pthread_cancel(threadArray[id].t_id);
		threadArray[id].active = 0;
		printf("A: Killed thread %d\n", id);
	}
	//pthread_mutex_unlock (&manager.lock);
}

void cleanup() {
	printf("A is quitting...\n");

	for (int i=0; i < count; i++){
		pthread_cancel(threadArray[i].t_id);
	}
	exit(0);
}

void* manager_thread (void* arg) {
	int fd = open(FIFO_TO_A, O_RDONLY);
	char command[50];

	while (1) {
		if (read(fd, command, sizeof(command)) > 0) { 
			if (strncmp (command, "CREATE_THREAD", 13)==0) 
				create_thread();
			else if (strncmp (command, "LIST_THREADS", 12)==0)
				list_threads();
			else if (strncmp (command, "EXIT", 4)==0)
				cleanup();
			else if (strncmp (command, "KILL_THREAD", 11)==0) {
				int id;
				if (sscanf (command+11, "%d", &id) == 1) {
					kill_thread (id);
				}
				else fprintf (stderr, "Invalid thread is provided for kill\n");
			}
		}
	}
	close(fd);
	return NULL;
	
}

void send_command (const char* cmd){
	int fd = open (FIFO_TO_B, O_WRONLY);
	if (write (fd, cmd, strlen(cmd)) < 0){
		perror("write");
	}
	close (fd);
}

void* input_thread (void* arg){
	char command[50];

	while (1){
		fgets (command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = 0;
		send_command (command);
	}
}

int main() {
	pthread_t manager_tid, input_tid;
	pthread_create(&manager_tid, NULL, manager_thread, NULL);
	pthread_create(&input_tid, NULL, input_thread, NULL);

	pthread_join(manager_tid, NULL);
	pthread_join(input_tid, NULL);
	return 0;
}
