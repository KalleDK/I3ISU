#include <iostream>
#include "garage.hpp"


using namespace std;

Garage::Garage(unsigned int maxQue, unsigned int spotMax) : MessageHandler(maxQue), parkingSpotMax(spotMax)
{
	parkingSpotsUsed = 0;
	
	EntryWay_ = new Door(maxQue, this, ENTRY);
	ExitWay_ = new Door(maxQue, this, EXIT);
	
	carEntryQueue_ = new std::queue<CarMsg*>;
	carExitQueue_ = new std::queue<CarMsg*>;
	osapi::Thread d1(EntryWay_);
	osapi::Thread d2(ExitWay_);
	d1.start();
	d2.start();
}

Garage::~Garage()
{
	delete EntryWay_;
	delete ExitWay_;
	delete carEntryQueue_;
	delete carExitQueue_;
}

void Garage::handleMsg(unsigned long id, osapi::Message*& msg)
{
	switch(id)
	{
		case CAR_WANTS_ENTRY :
			handleCarEntryReq(static_cast<CarMsg*>(msg));
			msg = NULL;
			break;
		case CAR_WANTS_EXIT :
			handleCarExitReq(static_cast<CarMsg*>(msg));
			msg = NULL;
			break;
		case DOOR_RDY :
			handleDoorRdy(static_cast<DoorMsg*>(msg));
			break;
		default:
			break;
	}
}

void Garage::handleCarEntryReq(CarMsg* msg)
{
	cout << "Car " << msg->car_id << " put into entry queue" << endl;
	carEntryQueue_->push(msg);
	if(EntryRdy_ && (parkingSpotsUsed < parkingSpotMax))
		sendCar(ENTRY);
}

void Garage::handleCarExitReq(CarMsg* msg)
{
	cout << "Car " << msg->car_id << " put into exit queue" << endl;
	carExitQueue_->push(msg);
	if(ExitRdy_)
		sendCar(EXIT);
}

void Garage::handleDoorRdy(DoorMsg* msg)
{
	if(msg->door_type){
		ExitRdy_ = true;
		if(!carExitQueue_->empty())
				sendCar(msg->door_type);
	} else {
		EntryRdy_ = true;
		if(!carEntryQueue_->empty())
			sendCar(msg->door_type);
	}
}

void Garage::sendCar(int type)
{
	Request* Car;

	if(!type){
		parkingSpotsUsed++;
		cout << "Sending car to Entry door" << endl;
		Car = carEntryQueue_->front();
		EntryWay_->send(Door::CAR_FROM_QUEUE, Car);
		carEntryQueue_->pop();
		EntryRdy_ = false;
	} else {
		parkingSpotsUsed--;
		cout << "Sending car to Exit door" << endl;
		ExitWay_->send(Door::CAR_FROM_QUEUE, carExitQueue_->front());
		carExitQueue_->pop();
		ExitRdy_ = false;
	}
	cout << "Garage:\t\t\t Cars in garage " << parkingSpotsUsed << endl;
}


