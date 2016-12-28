#ifndef DOOR_HPP_
#define DOOR_HPP_

#include <pthread.h>
#include <string.h>
#include "IDList.hpp"
#include "Message.hpp"
#include "Request.hpp"
#include "AI.hpp"

class Door : public AI
{
public:
	Door(std::string name, AI* garage, unsigned int type, unsigned int id);
private:
	bool Open();
	bool Close();

	void handleMsg(unsigned long id, Message*& msg);
	void handleOpenDoor(AI* car);
	void handlePassageComplete();
	void handleCheckQueue();

	bool state;
	unsigned int type;
	AI* garage;
};

#endif
