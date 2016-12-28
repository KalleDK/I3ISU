#include "Garage.hpp"

Garage::Garage(unsigned int max_size, unsigned int entry_num, unsigned int exit_num) : AI("Garage"), max_cars_inside(max_size)
{
	this->cars_inside = 0;
	this->entry_queue = new std::deque<AI*>;
	this->exit_queue = new std::deque<AI*>;
	this->idle_entry_doors = new std::deque<AI*>;
	this->idle_exit_doors = new std::deque<AI*>;
	this->entry_num = entry_num;
	this->exit_num = exit_num;
	for (int i = 0; i < entry_num; ++i)
	{
		entry_doors.push_back(new Door("Entry " + std::to_string(i+1), this, 0, i));
	}
	for (int i = 0; i < exit_num; ++i)
	{
		exit_doors.push_back(new Door("Exit " + std::to_string(i+1), this, 1, i));
	}
}

bool Garage::sendCarToDoor(std::deque<AI*>* car_queue, std::deque<AI*>* door_queue, int cars_inside_change)
{
	AI* car;
	AI* door;
	if (!car_queue->empty() && !door_queue->empty())
	{
		car = car_queue->front();
		door = door_queue->front();
		std::cout << getName() << "\tsending " << car->getName() << " to " << door->getName() << "\n";
		door->Send(ID_DOOR_OPEN_REQ, new Request(car));
		car_queue->pop_front();
		door_queue->pop_front();
		cars_inside += cars_inside_change;
		return true;
	}
	return false;
}

void Garage::run()
{
	AI::run();
	for (int i = 0; i < entry_num; ++i)
	{
		entry_doors[i]->run();
	}
	for (int i = 0; i < exit_num; ++i)
	{
		exit_doors[i]->run();
	}
}

void Garage::handleEntryReq(AI* car)
{
	std::cout << getName() << "\tadded " << car->getName() << " to entry queue\n";
	entry_queue->push_back(car);
	if (cars_inside < max_cars_inside)
		sendCarToDoor(entry_queue, idle_entry_doors, 1);
}

void Garage::handleExitReq(AI* car)
{
	std::cout << getName() << "\tadded " << car->getName() << " to exit queue\n";
	exit_queue->push_back(car);
	if (sendCarToDoor(exit_queue, idle_exit_doors, -1))
		if (cars_inside == max_cars_inside-1)
			sendCarToDoor(entry_queue, idle_entry_doors, 1);
}

void Garage::handleCarRequest(AI* door, unsigned int type)
{
	if (type == DOOR_TYPE_ENTRY) {
		idle_entry_doors->push_back(door);
 		if (cars_inside < max_cars_inside)
			sendCarToDoor(entry_queue, idle_entry_doors, 1);
	} else if (type == DOOR_TYPE_EXIT) {
		idle_exit_doors->push_back(door);
		if (sendCarToDoor(exit_queue, idle_exit_doors, -1))
			if (cars_inside == max_cars_inside-1)
				sendCarToDoor(entry_queue, idle_entry_doors, 1);
	}
	std::cout << getName() << "\tcars inside " << cars_inside << "\n";
}

void Garage::handleMsg(unsigned long id, Message*& msg)
{
	switch(id)
	{
		case ID_GARAGE_GET_ENTRY_CAR_REQ:
			handleCarRequest(static_cast<Request*>(msg)->ptr, DOOR_TYPE_ENTRY);
			break;
		case ID_GARAGE_GET_EXIT_CAR_REQ:
			handleCarRequest(static_cast<Request*>(msg)->ptr, DOOR_TYPE_EXIT);
			break;
		case ID_GARAGE_ENTRY_REQ:
			handleEntryReq(static_cast<Request*>(msg)->ptr);
			break;
		case ID_GARAGE_EXIT_REQ:
			handleExitReq(static_cast<Request*>(msg)->ptr);
			break;
		default:
			break;
	}
}
