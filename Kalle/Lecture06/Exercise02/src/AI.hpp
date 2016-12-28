#pragma once

#include <pthread.h>
#include <iostream>
#include <string>

#include "MsgQueue.hpp"
#include "Message.hpp"

class AI
{
public:
	AI(std::string name = "");
	void run();
	void Send(unsigned long id, Message* msg);
	const std::string getName();
	virtual ~AI();
private:
	std::string name;
	MsgQueue* mq;
	virtual void handleMsg(unsigned long id, Message*& msg) = 0;
	static void* thread_ai(void* this_ptr);
	AI* ai;
	pthread_t pid;
};
