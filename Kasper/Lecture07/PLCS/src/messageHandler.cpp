#include "messageHandler.hpp"

MessageHandler::MessageHandler(unsigned int maxQue)
{
	mq_ = new osapi::MsgQueue(maxQue);
	running_ = true;
}

MessageHandler::~MessageHandler()
{
	delete mq_;
}

void MessageHandler::run()
{
	while ( running_ )
	{	
		unsigned long id;
		osapi::Message* msg = mq_->receive(id);
		handleMsg (id, msg);
		delete msg ;
	}
}

void MessageHandler::send(unsigned long id, osapi::Message* msg)
{
	mq_->send(id, msg);
}