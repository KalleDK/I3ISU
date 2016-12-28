#include "Receiver.hpp"

void Receiver::handleMsg(unsigned long id, Message*& msg)
{
	std::cout << "Receiving\n";
	switch(id)
	{
		case RES_POINT3D:
			handleReceivePoint(static_cast<Point3D*>(msg));
			break;
	}
	std::cout << "Received\n";
}

void Receiver::handleReceivePoint(Point3D* p)
{
	std::cout << "(" << p->x << "." << p->y << "." << p->z << ")\n";
}
