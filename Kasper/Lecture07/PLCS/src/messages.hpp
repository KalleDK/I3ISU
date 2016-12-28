#pragma once
#include <osapi/Message.hpp>
#include <osapi/MsgQueue.hpp>

struct Request : public osapi::Message
{
	Request(osapi::MsgQueue* send) : sender(send) {};
	osapi::MsgQueue* sender;
};

struct CarMsg : public Request
{
	CarMsg(osapi::MsgQueue* send, int carid) : Request(send), car_id(carid) {};
	int car_id;
};

struct DoorMsg : public Request
{
	DoorMsg(osapi::MsgQueue* send, int doorid) : Request(send), door_type(doorid) {};
	int door_type;
};
