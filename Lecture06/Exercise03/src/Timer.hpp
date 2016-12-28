#pragma once

#include <unistd.h>
#include <iostream>
#include "IDList.hpp"
#include "AI.hpp"
#include "Event.hpp"

class Timer: public AI
{
public:
	Timer();
	void addEvent(AI* ai, unsigned int sleeptime, unsigned long id, Message* reply = NULL);
private:
	void executeEvent(Event* event);

	void handleMsg(unsigned long id, Message*& msg);
	void handleNewEvent(Event* event);
	void handleClock();
	std::deque<Event*> events;
};
