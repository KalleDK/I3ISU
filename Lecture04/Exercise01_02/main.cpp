#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <semaphore.h>
#include "Vector.hpp"

struct Shared
{
	Vector v;
	int error = 0;
	int success = 0;
	sem_t mtx;
};


struct thread_data
{
	Shared* shared;
	int wait;
	int id;
};

void* writer(void *void_shared_ptr)
{
	thread_data* data = (thread_data*)void_shared_ptr;
	while(data->shared->error < 50 && data->shared->success < 200000) {
		sem_wait(&data->shared->mtx);
		if (!data->shared->v.setAndTest(data->id))
		{
			++(data->shared->error);
			std::cout << "Error count: " << data->shared->error << "\n";
		} else {
			++(data->shared->success);
		}
		sem_post(&data->shared->mtx);
		usleep(data->wait);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int num_threads;
	int wait_thread;
	int err = 0;
	if (argc == 3) {
		num_threads = std::atoi(argv[1]);
		wait_thread = std::atoi(argv[2]);
	} else {
		std::cout << argv[0] << " THREADS WAIT\n\n";
		return -1;
	}
	Shared shared;
	thread_data* data_ptr;
	pthread_t threads[num_threads];

	err = sem_init(&shared.mtx, 0, 1);
	if (err == -1) {
		std::cout << "Error initialising semaphore\n";
		return -1;
	}

	std::cout << "Main: Creating threads\n";
        for(int t = 0; t < num_threads; ++t) {
        	std::cout << "Main: Creating thread #" << t << "\n";
		data_ptr = new thread_data;
		data_ptr->shared = &shared;
		data_ptr->wait = wait_thread;
		data_ptr->id = t;
                pthread_create(&threads[t], NULL, writer, (void *) data_ptr);
	}
	std::cout << "Main: Waiting for threads to finish\n";
        for(int t = 0; t < num_threads; ++t) {
		pthread_join(threads[t], NULL);
	}
	std::cout << "Success: " << shared.success << "\tErrors: " << shared.error << "\n";
}
