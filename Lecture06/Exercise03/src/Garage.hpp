#pragma once
#include <pthread.h>
#include <string>
#include <vector>
#include "Door.hpp"
#include "AI.hpp"
#include "IDList.hpp"


class Garage: public AI
{
public:
	Garage(unsigned int max_size, unsigned int entry_doors = 1, unsigned int exit_doors = 1);
	bool sendCarToDoor(std::deque<AI*>* car_queue, std::deque<AI*>* door_queue, int cars_inside_change);
	void run();
private:
	void handleMsg(unsigned long id, Message*& msg);
	void handleEntryReq(AI* car);
	void handleExitReq(AI* car);
	void handleCarRequest(AI* door, unsigned int type);

	std::vector<Door*> entry_doors;
	std::vector<Door*> exit_doors;
	std::deque<AI*>* entry_queue;
	std::deque<AI*>* idle_entry_doors;
	std::deque<AI*>* exit_queue;
	std::deque<AI*>* idle_exit_doors;
	unsigned int entry_num;
	unsigned int exit_num;
	unsigned int cars_inside;
	const unsigned int max_cars_inside;
};
