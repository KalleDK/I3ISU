#include "Door.hpp"

Door::Door(std::string name, AI* garage, unsigned int type, unsigned int id) : AI(name)
{
	this->garage = garage;
	this->cars_in_queue = false;
	this->type = type;
	this->occupied = false;
	state = false;
	if (type == DOOR_TYPE_ENTRY) {
		garage->Send(ID_GARAGE_GET_ENTRY_CAR_REQ, new Request(this));
	} else {
		garage->Send(ID_GARAGE_GET_EXIT_CAR_REQ, new Request(this));
	}
}

bool Door::Open()
{
	std::cout << getName() << "\tdoor opened\n";
	state = true;
}

bool Door::Close()
{
	std::cout << getName() << "\tdoor closed\n";
	state = false;
}

void Door::handleOpenDoor(AI* car)
{
	std::cout << getName() << "\tdoor opens for " << car->getName() << "\n";
	Open();
	car->Send(ID_CAR_PASSAGE_GRANTED, new Request(this));
}

void Door::handlePassageComplete()
{
	Close();
	occupied = false;
	Send(ID_DOOR_CHECK_QUEUE, NULL);
}

void Door::handleCheckQueue()
{
	if(!occupied)
	{
		std::cout << getName() << "\trequests a car\n";
		cars_in_queue = false;
		occupied = true;
		if (type == DOOR_TYPE_ENTRY) {
			garage->Send(ID_GARAGE_GET_ENTRY_CAR_REQ, new Request(this));
		} else {
			garage->Send(ID_GARAGE_GET_EXIT_CAR_REQ, new Request(this));
		}
	}
}

void Door::handleCarArrived()
{
	std::cout << getName() << "\twas told there would be cars\n";
	cars_in_queue = true;
	Send(ID_DOOR_CHECK_QUEUE, NULL);
}

void Door::handleQueueEmpty()
{
	occupied = false;
	if (cars_in_queue)
	{
		Send(ID_DOOR_CHECK_QUEUE, NULL);
	}
}
	

void Door::handleMsg(unsigned long id, Message*& msg)
{
	switch(id)
	{
		case ID_DOOR_OPEN_REQ:
			handleOpenDoor(static_cast<Request*>(msg)->ptr);
			break;
		case ID_DOOR_PASSAGE_COMPLETE:
			handlePassageComplete();
			break;
		case ID_DOOR_CHECK_QUEUE:
			handleCheckQueue();
			break;
		case ID_DOOR_CAR_ARRIVED:
			handleCarArrived();
			break;
		case ID_DOOR_QUEUE_EMPTY:
			handleQueueEmpty();
			break;
		default:
			break;
	}
}
