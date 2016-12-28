#pragma once
#include "AI.hpp"
#include "Message.hpp"

class Request: public Message
{
public:
	Request(AI* ptr)
	{
		this->ptr = ptr;
	}
	AI* ptr;
};
