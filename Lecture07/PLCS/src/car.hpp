#pragma once
#include <osapi/Timer.hpp>
#include "messageHandler.hpp"
#include "messages.hpp"
#include "garage.hpp"

class Garage;
class Car : public MessageHandler
{
public:
	enum
	{
		WAKE_UP_LITTLE_CAR,
		GO_AHEAD,
	};
	
	Car(unsigned int maxQueue, Garage* plPtr, unsigned int nr, unsigned int timeOut);
private:
	void handleMsg(unsigned long id, osapi::Message*& msg);
	void handleWakeUp(CarMsg* msg);
	void handleParking(DoorMsg* msg);
	
	
	bool parked_;
	Garage* pl_;
	unsigned int carId;
	osapi::ITimerId*  carTimer_;
};