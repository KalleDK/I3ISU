#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#define ENTRY 0
#define EXIT 1

class Door {
private:
	queue_size = 0;
	door_mtx = PTHREAD_MUTEX_INITIALIZER;
public:
	void addCar() {
		pthread_mutex_lock(&door_mtx);
		++queue_size;
		pthread_mutex_unlock(&door_mtx);
	}
	bool hasQueue();
}

class ParkingLot {
private:
	unsigned int cars_parked;
	Door doors[2];
public:
	void OpenDoor(int id);
	void CloseDoor(int id);
	bool isFull();
	bool isEmpty();
	bool hasQueu(int id);
}

void* exitguard(void *parkinglot_ptr) {
	while(1) {
		
	}
}

void* car(void *id_ptr) {
	int id = (int) id_ptr;
	while(1) {
	}
}

int main(int argc, char *argv[])
{
	ParkingLot p;
	pthread_t entryguard;
	pthread_t exitguard;
	pthread_t cars[10];
	pthread_create(&entrydoor, NULL, entryguard, NULL);
	pthread_create(&exitdoor, NULL, exitguard, NULL);
	for (int i = 0; i < 10; ++i) {
		pthread_create(&cars[i], NULL, car, (void*)i);
	}
	std::cout << "Main: Creating threads\n";
	std::cout << "Main: Waiting for threads to finish\n";
	pthread_exit(NULL);
}
