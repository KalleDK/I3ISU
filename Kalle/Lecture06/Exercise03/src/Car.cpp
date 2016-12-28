#include "Car.hpp"

Car::Car(std::string name, AI* garage, Timer* timer, unsigned int sleeptime) : AI(name) {
	this->parked = false;
	this->sleeptime = sleeptime;
	this->garage = garage;
	this->timer = timer;
	this->timer->addEvent(this, this->sleeptime, ID_CAR_CHANGE_LOCATION);
}

const char* Car::getLocation() {
	if (this->parked) {
		return "parked";
	}
	else {
		return "outside";
	}
}


void Car::handleChangeLocation()
{
	if (!parked) {
		std::cout << getName() <<  "\trequesting entry\n";
		garage->Send(ID_GARAGE_ENTRY_REQ, new Request(this)); 
	} else {
		std::cout << getName() <<  "\trequesting exit\n";
		garage->Send(ID_GARAGE_EXIT_REQ, new Request(this)); 
	}
}

void Car::handlePassage(AI* door)
{
	std::cout << getName() << "\tis driving through the " << door->getName() << " door\n";
	parked = !parked;
	std::cout << getName() << "\tis now " << getLocation() << "\n";
	door->Send(ID_DOOR_PASSAGE_COMPLETE, NULL);
	timer->addEvent(this, sleeptime, ID_CAR_CHANGE_LOCATION);
}

void Car::handleMsg(unsigned long id, Message*& msg)
{
	switch(id)
	{
		case ID_CAR_CHANGE_LOCATION:
			this->handleChangeLocation();
			break;
		case ID_CAR_PASSAGE_GRANTED:
			this->handlePassage(static_cast<Request*>(msg)->ptr);
			break;
		default:
			break;
	}
}
