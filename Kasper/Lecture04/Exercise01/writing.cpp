#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "Vector.hpp"

#define NUM_T 100

using namespace std;

Vector toWrite;
int errors = 0;
unsigned int sleep_time = 500;
pthread_mutex_t vectorMtx = PTHREAD_MUTEX_INITIALIZER;

static void * writer(void * arg)
{
	long tid = (long)arg;
	while(errors < 50)
	{
		pthread_mutex_lock(&vectorMtx);
		if(!toWrite.setAndTest(tid))
		{
			cout << "Error from thread " << tid << endl;
			++errors;
		}
		pthread_mutex_unlock(&vectorMtx);
		usleep(sleep_time);
	}
	return (void*)tid;
}



int main(int argc, char *argv[])
{
	
	
	unsigned int numThreads;
	int s;
	void* res;

	if( argc >= 3){
		 numThreads = atoi(argv[1]);
		cout << argv[1] << numThreads << endl;
		if (!(numThreads  > 0 && numThreads < 101)){
			numThreads = 50;
		}
		sleep_time = atoi(argv[2]);
		cout << argv[2] << sleep_time << endl;
		if(!(sleep_time < 100000)){
			sleep_time = 1000;
		}
	}else{
		cout << "Not enough arguments specifiy atleast two: Number of threads and sleep time" << endl;
		return -1;
	}
	pthread_t t[NUM_T];
	cout << "Main is starting the vector! " << "With " << numThreads << " threads and sleep time of " << sleep_time << endl;

	for(unsigned int i = 0; i < numThreads; ++i)
	{
		s = pthread_create(&t[i], NULL, writer, (void *)i);
		if(s != 0)
			return 1;
		cout << "Created thread: " << i << endl;
	}
	
	for(int j = 0; j < numThreads; ++j)
	{
		s = pthread_join(t[j], &res);
		if(s != 0)
			return 1;
		cout << "Writer returned " << (int)res << "\n";
	}
	cout << "we are done\n";
	return 0;
}
