#include "Sender.hpp"

Sender::Sender(AI* receiver, unsigned int sleeptime)
{
	this->receiver = receiver;
	this->sleeptime = sleeptime;
	this->Send(REQ_POINT3D, NULL);
	this->count = 0;
}

void Sender::handleMsg(unsigned long id, Message*& msg)
{
	switch(id)
	{
		case REQ_POINT3D:
			handleSendPoint();
			break;
	}
}

void Sender::handleSendPoint()
{
	std::cout << "Sending\n";
	Point3D* p = new Point3D(count, count*2, count*3);
	receiver->Send(RES_POINT3D, static_cast<Message*>(p));
	++count;
	std::cout << "Sent\n";
	sleep(1);
	this->Send(REQ_POINT3D, NULL);
}
