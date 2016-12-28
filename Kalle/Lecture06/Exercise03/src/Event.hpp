#pragma once
#include "Message.hpp"
#include "Request.hpp"
#include "AI.hpp"

class Event : public Request
{
public:
	Event(AI* ai, unsigned int sleeptime, unsigned long id, Message* msg) : Request(ai)
	{
		this->sleeptime = sleeptime;
		this->id = id;
		this->msg = msg;
	}
	unsigned int sleeptime;
	unsigned long id;
	Message* msg;
};
