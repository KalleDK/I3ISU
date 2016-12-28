#pragma once
#include "Message.hpp"

#define REQ_POINT3D 1
#define RES_POINT3D 2

struct Point3D: public Message
{
public:
	Point3D(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	int x;
	int y;
	int z;
};
