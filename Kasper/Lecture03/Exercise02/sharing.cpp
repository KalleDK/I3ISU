#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int shared = 0;

static void * incrementer(void *)
{
	while(shared < 500)
	{
		shared++;
		sleep(1);
	}
	return (void *) shared;
}

static void * reader(void *)
{
	while(shared < 500)
	{
		cout << "shared is: " << shared << "\n";
		sleep(1);
	}
	return (void *) shared;
}



int main(void)
{

	pthread_t t1,t2;
	int s;
	void* res;

	cout << "Main is starting the counter!\n";

	s = pthread_create(&t1, NULL, incrementer, NULL);
	if(s != 0)
		return 1;

	s = pthread_create(&t2, NULL, reader, NULL);
	if(s != 0)
		return 1;

	s = pthread_join(t1, &res);
	if(s != 0)
		return 1;

	cout << "Incrementer returned" << (int)res << "\n";

	s = pthread_join(t2, &res);
	if(s != 0)
		return 1;

	cout << "Reader returned" << (int)res << "\n";

	cout << "we are done";
	return 0;
}
