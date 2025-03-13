#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long sum(int n) {
	int m = 0;
	for(long long i = 0; i <= n; i++) {
		m += i;
	}
	return m;
}

int main(int argc, char* argv[]) {
	clock_t start = clock();
	if(argc != 2) {
		printf("./sumserial n\n");
	}
	int n = atoi(argv[1]);
	printf("Sum serial, sum(n) = %lld\n", sum(n));
	clock_t end = clock();
	double time = (double) (end - start) / CLOCKS_PER_SEC;
	printf("Execution time: %fs\n", time);	
}
