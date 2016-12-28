#ifndef SENDER_HPP_
#define SENDER_HPP_

#include <iostream>
#include <unistd.h>
#include "Point3D.hpp"
#include "AI.hpp"

class Sender : public AI
{
public:
	Sender(AI* receiver, unsigned int sleeptime = 1);

private:
	void handleMsg(unsigned long id, Message*& msg);
	void handleSendPoint();

	unsigned int sleeptime;
	unsigned int count;
	AI* receiver;
};

#endif
