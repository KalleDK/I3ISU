#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Vector.hpp"

struct thread_data
{
	Vector* v;
	int* error;
	int wait;
	int id;
	pthread_mutex_t* mtx;
	
};

void* writer(void *void_shared_ptr)
{
	thread_data* shared_ptr = (thread_data*)void_shared_ptr;
	while(*shared_ptr->error < 50) {
		pthread_mutex_lock(shared_ptr->mtx);
		if (!shared_ptr->v->setAndTest(shared_ptr->id))
		{
			++(*shared_ptr->error);
			std::cout << "Error count: " << *shared_ptr->error << "\n";
		}
		pthread_mutex_unlock(shared_ptr->mtx);
		std::cout << ".";
		usleep(shared_ptr->wait);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int num_threads = 100;
	int wait_thread = 50000;
	if (argc == 3) {
		num_threads = std::atoi(argv[1]);
		wait_thread = std::atoi(argv[2]);
	} else {
		return -1;
	}
	pthread_t threads[num_threads];
	Vector shared;
	int error = 0;
	thread_data* data_ptr;
	pthread_mutex_t* mtx = new pthread_mutex_t;
	*mtx = PTHREAD_MUTEX_INITIALIZER;

	std::cout << "Main: Creating threads\n";
        for(int t = 0; t < num_threads; ++t) {
        	std::cout << "Main: Creating thread #" << t << "\n";
		data_ptr = new thread_data;
		data_ptr->v = &shared;
		data_ptr->error = &error;
		data_ptr->wait = wait_thread;
		data_ptr->id = t;
		data_ptr->mtx = mtx;
                pthread_create(&threads[t], NULL, writer, (void *) data_ptr);
	}
	std::cout << "Main: Waiting for threads to finish\n";
	pthread_exit(NULL);
}
