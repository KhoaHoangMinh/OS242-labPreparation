#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


typedef struct {
	long long start;
	long long end;
	long long sum;
} ThreadData;

void* partial_sum(void* arg) {
	ThreadData* data = (ThreadData*) arg;
	data->sum = 0;
	for(long long i = data->start; i <= data->end; i++) {
		data->sum += i;
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	clock_t startTime = clock();
	if(argc != 3) {
		printf("./sum_multi_thread <numThread> <n>");
		return 1;
	}

	int numThreads = atoi(argv[1]);
	long long n = atoll(argv[2]);

	pthread_t threads[numThreads];
	ThreadData data[numThreads];

	long long range = n / numThreads;
	long long remainder = n % numThreads;
	long long start = 1;

	for(int i = 0; i < numThreads; i++) {
		data[i].start = start;
		data[i].end = start + range - 1;

		if(i == numThreads - 1) {
			data[i].end += remainder;
		}
		// printf("%lld %lld, ", data[i].start, data[i].end);
		
		pthread_create(&threads[i], NULL, partial_sum, &data[i]);
		start = data[i].end + 1;
	}
	long long totalSum = 0;
	for(int i = 0; i < numThreads; i++) {
		pthread_join(threads[i], NULL);
		totalSum += data[i].sum;
	}
	printf("Multi-threaded, sum(n) = %lld\n", totalSum);
	clock_t endTime = clock();
	double exeTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
	printf("Execution time: %fs\n", exeTime);
	return 0;
}
