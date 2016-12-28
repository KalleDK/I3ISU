#include "AI.hpp"
AI::AI(std::string name)
{
	this->name = name;
	this->mq = new MsgQueue(100);
	this->ai = this;
}

void AI::run()
{
	std::cout << "Running " << getName() << "\n";
	pthread_create(&this->pid, NULL, AI::thread_ai, (void*)this);
}

AI::~AI()
{
	delete mq;
}

void AI::Send(unsigned long id, Message* msg)
{
	this->mq->send(id, msg);
}

void* AI::thread_ai(void* void_ptr)
{
	AI* ai = static_cast<AI*>(void_ptr)->ai;
	Message* msg;
	unsigned long id;
	for(;;)
	{
		msg = ai->mq->receive(id);
		ai->handleMsg(id, msg);
		delete msg;
	}
}

const std::string AI::getName()
{
	return name;
}
