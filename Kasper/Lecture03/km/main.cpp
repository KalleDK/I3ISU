#include <pthread.h>
#include <iostream>
#define NUM_THREADS 10

void *CountUp(void *threadid)
{
	long tid;
	tid = (long)threadid;
	std::cout << tid << "\n";
	for (int i=0; i < 100; ++i) {
		std::cout << tid << ": " << i << std::endl;
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	long t;
	pthread_t threads[NUM_THREADS];
	

	for(t = 0; t < NUM_THREADS; ++t) {
		pthread_create(&threads[t], NULL, CountUp, (void *)t);
	}
	pthread_exit(NULL);
	return 0;
}
