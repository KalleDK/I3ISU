#include <pthread.h>
#include <iostream>
#include <unistd.h>
#define NUM_THREADS 2

void *CountUp(void *tid_ptr)
{
	int tid = *(int*)tid_ptr;

	for (int i=0; i < 10; ++i) {
		std::cout << "Hello #" << i << " from thread " << tid << std::endl;
		sleep(1);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];

	std::cout << "Main: Creating threads\n";
	for(int t = 0; t < NUM_THREADS; ++t) {
		pthread_create(&threads[t], NULL, CountUp, (void *) new int(t));
	}
	std::cout << "Main: Waiting for threads to finish\n";
	pthread_exit(NULL);
}
