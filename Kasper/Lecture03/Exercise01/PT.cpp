#include<iostream>
#include<pthread.h>
#include <unistd.h>

using namespace std;

static void * threadPrint(void * arg)
{
	int id = (int)arg;
	int count = 0;
	while(count < 10)
	{
		cout << "Hello #" << count << " from thread " << id << endl;
		count++;
		sleep(1);
	}

	return (void *) id;
}



int main(void)
{
	pthread_t t1, t2 ;
	int s;
	void *res;
	int numb = 0;

	cout << "Main: Creating threads" << endl;	

	s = pthread_create(&t2, NULL, threadPrint,(void *) numb);
	if (s != 0)
		return 1;

	numb++;
	s = pthread_create(&t1, NULL, threadPrint,(void *) numb);
	if (s != 0)
		return 1;

	cout << "Main Waiting for threads to finish" << endl;	

	s = pthread_join(t1, &res);
	if (s != 0)
		return 2;

	cout << "Thred " << (int)res << " terminates" << endl;

	s = pthread_join(t2, &res);
	if (s != 0)
		return 2;

	cout << "Thred " << (int)res << " terminates" << endl;
	cout << "Main: exiting" << endl;
	return 0;
}
