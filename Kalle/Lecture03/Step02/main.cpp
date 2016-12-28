#include <pthread.h>
#include <iostream>
#include <unistd.h>
#define NUM_THREADS 2

void* reader (void *void_shared_ptr)
{
	int* shared_ptr = (int*)void_shared_ptr;
	while(true) {
		++(*shared_ptr);
		sleep(2);
	}
	pthread_exit(NULL);
}

void* incrementer(void *void_shared_ptr)
{
	int* shared_ptr = (int*)void_shared_ptr;
	while(true) {
		std::cout << *shared_ptr << "\n";
		sleep(3);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t increment, read;
	int shared = 0;

	std::cout << "Main: Creating threads\n";
	pthread_create(&increment, NULL, incrementer, (void *) &shared);
	pthread_create(&read, NULL, reader, (void *) &shared);
	std::cout << "Main: Waiting for threads to finish\n";
	pthread_exit(NULL);
}
