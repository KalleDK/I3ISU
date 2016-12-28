#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

unsigned int MAX_CARS = 0;
unsigned int CARS = 0;

unsigned int carsInLot = 0;

pthread_mutex_t car_mtx = PTHREAD_MUTEX_INITIALIZER;

bool car_waiting_entry = false;
bool entry_door_open = false;
pthread_mutex_t entry_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t entry_cond = PTHREAD_COND_INITIALIZER;

bool car_waiting_exit = false;
bool exit_door_open = false;
pthread_mutex_t exit_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t exit_cond = PTHREAD_COND_INITIALIZER;

void* entryguard(void *void_shared_ptr) {
	while(1) {
//		std::cout << "Entry: Waiting for car\n";
		pthread_mutex_lock(&entry_mtx);
		while (car_waiting_entry == false) {
			pthread_cond_wait(&entry_cond,&entry_mtx);
		}
		entry_door_open = true;
//		std::cout << "Entry: Open\n";
		pthread_cond_broadcast(&entry_cond);
		while (car_waiting_entry == true || carsInLot >= MAX_CARS) {
			pthread_cond_wait(&entry_cond,&entry_mtx);
		}
		entry_door_open = false;
		pthread_mutex_lock(&car_mtx);
		carsInLot++;
		std::cout << "Cars in lot: " << carsInLot << "\n";
		pthread_mutex_unlock(&car_mtx);
//		std::cout << "Entry: Closed\n";
		pthread_cond_broadcast(&entry_cond);
		pthread_mutex_unlock(&entry_mtx);
	}
}

void* exitguard(void *void_shared_ptr) {
	while(1) {
//		std::cout << "Exit: Waiting for car\n";
		pthread_mutex_lock(&exit_mtx);
		while (car_waiting_exit == false) {
			pthread_cond_wait(&exit_cond,&exit_mtx);
		}
		exit_door_open = true;
//		std::cout << "Exit: Open\n";
		pthread_cond_broadcast(&exit_cond);
		while (car_waiting_exit == true) {
			pthread_cond_wait(&exit_cond,&exit_mtx);
		}
		exit_door_open = false;
		pthread_mutex_lock(&car_mtx);
		carsInLot--;
		pthread_cond_broadcast(&entry_cond);
		pthread_mutex_unlock(&car_mtx);
//		std::cout << "Exit: Closed\n";
		pthread_cond_broadcast(&exit_cond);
		pthread_mutex_unlock(&exit_mtx);
	}
}

void* car(void *id_ptr) {
	int id = (int) id_ptr;
	while(1) {
//		std::cout << "Car #" << id << " wants to park\n";
		pthread_mutex_lock(&entry_mtx);
		while (car_waiting_entry == true || entry_door_open == true) {	
			pthread_cond_wait(&entry_cond,&entry_mtx);
		}
		car_waiting_entry = true;
//		std::cout << "Car #" << id << " is in queue to entry\n";
		pthread_cond_broadcast(&entry_cond);
		while (entry_door_open == false) {
			pthread_cond_wait(&entry_cond,&entry_mtx);
		}
		car_waiting_entry = false;
                pthread_cond_broadcast(&entry_cond);
//		std::cout << "Car #" << id << " parked\n";
		pthread_mutex_unlock(&entry_mtx);
		sleep(rand()%10);

//		std::cout << "Car #" << id << " wants to exit\n";
		pthread_mutex_lock(&exit_mtx);
		while (car_waiting_exit == true || exit_door_open == true) {	
			pthread_cond_wait(&exit_cond,&exit_mtx);
		}
		car_waiting_exit = true;
//		std::cout << "Car #" << id << " is in queue to exit\n";
		pthread_cond_broadcast(&exit_cond);
		while (exit_door_open == false) {
			pthread_cond_wait(&exit_cond,&exit_mtx);
		}
		car_waiting_exit = false;
                pthread_cond_broadcast(&exit_cond);
//		std::cout << "Car #" << id << " idle\n";
		pthread_mutex_unlock(&exit_mtx);
		sleep(rand()%10);
	}
}

int main(int argc, char *argv[])
{
	if(argc == 3){
		int temp = atoi(argv[1]);
		if(temp > 50){
			CARS = 50; 
		}else{
			CARS = temp;
		}
		temp = atoi(argv[2]);
		if(temp > 60){
			MAX_CARS = 60;
		}else{
			MAX_CARS = temp;
		}
	}else{
		std::cout << "Specify atleast two arguments: number of cars and spaces in lot!\n";
		return -1;
	}
	

	pthread_t entrydoor;
	pthread_t exitdoor;
	pthread_t cars[CARS];
	pthread_create(&entrydoor, NULL, entryguard, NULL);
	pthread_create(&exitdoor, NULL, exitguard, NULL);
	for (int i = 0; i < CARS; ++i) {
		pthread_create(&cars[i], NULL, car, (void*)i);
	}
	std::cout << "Main: Creating threads\n";
	std::cout << "Main: Waiting for threads to finish\n";
	pthread_exit(NULL);
}
