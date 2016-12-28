#include <iostream>
#include "door.hpp"

using namespace std;

Door::Door(unsigned int maxQue, Garage* plPtr, unsigned int nr) : MessageHandler(maxQue), pl_(plPtr), type_(nr)
{
	active_ = false;
	pl_->send(Garage::DOOR_RDY, new DoorMsg(this->mq_, type_));
	cout << "Door constructed " << endl;
}

void Door::handleMsg(unsigned long id, osapi::Message*& msg)
{
	switch(id)
	{
		case CAR_FROM_QUEUE :
			handleCarFromQueue(static_cast<CarMsg*>(msg));
			break;
		case CAR_PASSED_DOOR :
			handleCarPassed(static_cast<CarMsg*>(msg));
			break;
		case DOOR_CHECK_QUEUE :
			handleWakeUp();
			break;
		default:
			break;
	}
}

void Door::handleCarFromQueue(CarMsg* msg)
{
	if(!type_){
		cout << "Car " << msg->car_id << " is premittet to enter" << endl;
		msg->sender->send(Car::GO_AHEAD, new DoorMsg(this->mq_, ENTRY));
	} else {
		cout << "Car " << msg->car_id << " is premittet to leave" << endl;
		msg->sender->send(Car::GO_AHEAD, new DoorMsg(this->mq_, EXIT));
	}
}

void Door::handleCarPassed(CarMsg* msg)
{
	if(type_){
		cout << "ExitDoor is closed " << endl;
	} else {
		cout << "EntryDoor is closed " << endl;
	}
	pl_->send(Garage::DOOR_RDY, new DoorMsg(this->mq_, type_));
}
