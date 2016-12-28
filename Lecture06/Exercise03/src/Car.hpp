#ifndef CAR_HPP_
#define CAR_HPP_

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
#include "Message.hpp"
#include "Request.hpp"
#include "AI.hpp"
#include "Timer.hpp"
#include "IDList.hpp"

class Car : public AI
{
public:
	Car(std::string name, AI* garage, Timer* timer, unsigned int sleeptime = 1);

	const char* getLocation();

private:
	void handleMsg(unsigned long id, Message*& msg);
	void handleChangeLocation();
	void handlePassage(AI* door);

	bool parked;
	unsigned int sleeptime;
	Timer* timer;
	AI* garage;
};

#endif
