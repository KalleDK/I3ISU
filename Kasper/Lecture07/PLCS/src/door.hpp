#pragma once
#include "messageHandler.hpp"
#include "messages.hpp"
#include "car.hpp"
#include "garage.hpp"

class Garage;
class Door : public MessageHandler
{
public:
	enum
	{
		CAR_FROM_QUEUE,
		CAR_PASSED_DOOR,
		DOOR_CHECK_QUEUE,
	};
	
	Door(unsigned int maxQueue, Garage* plPtr, unsigned int type_);
	
private:
	void handleMsg(unsigned long id, osapi::Message*& msg);
	void handleCarFromQueue(CarMsg* msg);
	void handleCarPassed(CarMsg* msg);
	
	Garage* pl_;
	unsigned int type_;

};