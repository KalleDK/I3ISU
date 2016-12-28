#ifndef RECEIVER_HPP_
#define RECEIVER_HPP_

#include <iostream>
#include "Point3D.hpp"
#include "AI.hpp"

class Receiver : public AI
{
private:
	void handleMsg(unsigned long id, Message*& msg);
	void handleReceivePoint(Point3D* p);
};

#endif
