#include <iostream>
#include <pthread.h>
#include "Car.hpp"
#include "Door.hpp"
#include "Garage.hpp"
#include "Timer.hpp"

#define CAR_NUMBER 20
#define GARAGE_MAX_SIZE 10
#define ENTRY_DOORS 3
#define EXIT_DOORS 3

int main(void)
{
	Timer* t = new Timer();
	t->run();
	Garage* g = new Garage(GARAGE_MAX_SIZE, ENTRY_DOORS, EXIT_DOORS);
	g->run();
	Car* cars[CAR_NUMBER];
	for( int i = 0; i < CAR_NUMBER; ++i)
	{
		cars[i] = new Car("Car " + std::to_string(i+1), g, t, rand() % CAR_NUMBER );
		cars[i]->run();
	}
	for(;;)
	{
		sleep(1);
	}
}
