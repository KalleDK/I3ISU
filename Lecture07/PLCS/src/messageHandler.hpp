#pragma once
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Message.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Timer.hpp>
#include <osapi/Log.hpp>
#include <osapi/Utility.hpp>


class MessageHandler : public osapi::ThreadFunctor
{
public:
	MessageHandler(unsigned int maxQueue);
	virtual ~MessageHandler();
	void send(unsigned long id, osapi::Message* msg);
	osapi::MsgQueue* mq_;
	
private:
	virtual void handleMsg(unsigned long id, osapi::Message*& msg) = 0; 
	bool running_;
	
protected:
	virtual void run();
};