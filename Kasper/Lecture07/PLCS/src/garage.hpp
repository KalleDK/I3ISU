#pragma once
#include <queue>
#include "messages.hpp"
#include "messageHandler.hpp"
#include "car.hpp"
#include "door.hpp"
#define ENTRY 0
#define EXIT 1
class Door;
//class Car;

class Garage : public MessageHandler
{
public:
	enum
	{
		CAR_WANTS_ENTRY,
		CAR_WANTS_EXIT,
		DOOR_RDY,
		DOOR_CHECK_QUEUE_EXIT,
	};
	
	Garage(unsigned int maxQueue, unsigned int parkingSpotMax);
	~Garage();
	
private:
	void handleMsg(unsigned long id, osapi::Message*& msg);
	void handleCarEntryReq(CarMsg* msg);
	void handleCarExitReq(CarMsg* msg);
	void handleDoorRdy(DoorMsg* msg);
	void sendCar(int type);
	
	Door* EntryWay_;
	Door* ExitWay_;
	
	bool EntryRdy_;
	bool ExitRdy_;
	
	std::queue<CarMsg*>* carEntryQueue_;
	std::queue<CarMsg*>* carExitQueue_;

	unsigned int parkingSpotMax;
	unsigned int parkingSpotsUsed;
};