#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Utility.hpp>
#include "car.hpp"
#include "garage.hpp"

#define CARS 10
#define PLCS_SIZE 3
#define QUEUE_SIZE 50


int main()
{
	Garage PLCS(QUEUE_SIZE, PLCS_SIZE);
	osapi::Thread g(&PLCS);
	g.start();
	Car* Cars[CARS];
	osapi::Thread* c[CARS];
	for(int i = 0; i < CARS; ++i)
	{
		Cars[i] = new Car(QUEUE_SIZE, &PLCS, i+1, (rand() % 1000) + 1000);
		c[i] = new osapi::Thread(Cars[i]);
		c[i]->start();
	}
	while(1)
	{
		osapi::sleep(1000);
	}
}