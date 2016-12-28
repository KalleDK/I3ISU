#include <iostream>
#include "car.hpp"

using namespace std;

Car::Car(unsigned int maxQue, Garage* plPtr, unsigned int nr, unsigned int timeOut) : MessageHandler(maxQue), pl_(plPtr), carId(nr)
{
	carTimer_ = osapi::createNewTimer(mq_, WAKE_UP_LITTLE_CAR);
	carTimer_->arm(timeOut); // Timeout in 1sec
	parked_ = false;
}

void Car::handleMsg(unsigned long id, osapi::Message*& msg)
{
	switch(id)
	{
		case WAKE_UP_LITTLE_CAR :
			handleWakeUp(static_cast<CarMsg*>(msg));
			break;
		case GO_AHEAD :
			handleParking(static_cast<DoorMsg*>(msg));
			break;
		default:
			break;
	}
}

void Car::handleWakeUp(CarMsg* msg)
{
	if(parked_)
	{
		cout << "Car " << carId << " wants to leave" << endl;
		pl_->send(Garage::CAR_WANTS_EXIT, new CarMsg(this->mq_, carId));
	} 
	else 
	{
		cout << "Car " << carId << " wants to enter" << endl;
		pl_->send(Garage::CAR_WANTS_ENTRY, new CarMsg(this->mq_, carId));
	}
	
}

void Car::handleParking(DoorMsg* msg)
{
	if(parked_)
	{
		cout << "Car " << carId << " is leaving" << endl;
		msg->sender->send(Door::CAR_PASSED_DOOR, new DoorMsg(this->mq_, EXIT));
		parked_ = !parked_;
	}
	else
	{
		cout << "Car " << carId << " is parking" << endl;
		msg->sender->send(Door::CAR_PASSED_DOOR, new DoorMsg(this->mq_, ENTRY));
		parked_ = !parked_;
	}
	carTimer_->reArm();
}
