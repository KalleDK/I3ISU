#include <pthread.h>
#include <iostream>
#include <unistd.h>

#include "Vector.hpp"

#define NUM_T 50

using namespace std;

Vector toWrite;
int errors = 0;

static void * writer(void * arg)
{
	long tid = (long)arg;
	while(errors < 50)
	{
		if(!toWrite.setAndTest(tid))
		{
			cout << "Error from thread " << tid << endl;
			++errors;
		}
		sleep(1);
	}
	return (void*)tid;
}



int main(void)
{

	pthread_t t[NUM_T];
	int s;
	void* res;

	cout << "Main is starting the vector!\n";

	for(int i = 0; i < NUM_T; ++i)
	{
		s = pthread_create(&t[i], NULL, writer, (void *)i);
		if(s != 0)
			return 1;
	}
	
	for(int j = 0; j < NUM_T; ++j)
	{
		s = pthread_join(t[j], &res);
		if(s != 0)
			return 1;
		cout << "Writer returned " << (int)res << "\n";
	}
	cout << "we are done\n";
	return 0;
}
