#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "Vector.hpp"
#define NUM_THREADS 100

struct thread_data
{
	Vector* v;
	int* error;
	int id;
};

void* writer(void *void_shared_ptr)
{
	thread_data* shared_ptr = (thread_data*)void_shared_ptr;
	while(*shared_ptr->error < 50) {
		if (!shared_ptr->v->setAndTest(shared_ptr->id))
		{
			++(*shared_ptr->error);
			std::cout << "Error count: " << *shared_ptr->error << "\n";
		}
		sleep(1);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	Vector shared;
	int error = 0;
	thread_data* data_ptr;

	std::cout << "Main: Creating threads\n";
        for(int t = 0; t < NUM_THREADS; ++t) {
        	std::cout << "Main: Creating thread #" << t << "\n";
		data_ptr = new thread_data;
		data_ptr->v = &shared;
		data_ptr->error = &error;
		data_ptr->id = t;
                pthread_create(&threads[t], NULL, writer, (void *) data_ptr);
	}
	std::cout << "Main: Waiting for threads to finish\n";
	pthread_exit(NULL);
}
