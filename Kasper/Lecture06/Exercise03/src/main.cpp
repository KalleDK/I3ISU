#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "MsgQueue.hpp"

using namespace std;

struct Point3D : public Message
{
	int x;
	int y;
	int z;
};

struct Point4D : public Message
{
	int x;
	int y;
	int z;
	int t;
};


void ReceiverHandler(unsigned long id, Message* msg)
{
	switch(id){
	case 1:
	{
		Point3D* P3D = static_cast<Point3D*>(msg);
		cout << " x: " << P3D->x << " y: " << P3D->y << " z: " << P3D->z << "\n";
		break;
	}
	case 2:
	{
		Point4D* P4D = static_cast<Point4D*>(msg);
		cout << " x: " << P4D->x << " y: " << P4D->y << " z: " << P4D->z << " t: " << P4D->t << "\n";
		break;
	}
	default: 
		cout << "Nothing to see here\n";
		break;
		 
	}
}

void* Sender(void* data)
{
	MsgQueue* mq = static_cast<MsgQueue*> (data);
	while(1)
	{
		Point3D* hat = new Point3D();
		hat->x = rand() % 10;
		hat->y = rand() % 10;
		hat->z = rand() % 10;
		mq->send(1, hat);
		sleep(rand()%10);
	}
}

void* Sender2(void* data)
{
	MsgQueue* mq = static_cast<MsgQueue*> (data);
	while(1)
	{
		Point4D* hat = new Point4D();
		hat->x = rand() % 10;
		hat->y = rand() % 10;
		hat->z = rand() % 10;
		hat->t = rand() % 10;
		mq->send(2, hat);
		sleep(rand()%10);
	}
}

void* Receiver(void* data)
{
	MsgQueue* mq = static_cast<MsgQueue*> (data);
	while(1)
	{
		unsigned long id;
		Message* msg = mq->receive(id);
		ReceiverHandler(id,msg);
		delete msg;
	}
}

int main()
{
	MsgQueue point3DQue(20);
	pthread_t SenderThread, ReceiverThread, Sender2Thread;
	pthread_create(&SenderThread, NULL, Sender, &point3DQue);
	pthread_create(&Sender2Thread, NULL, Sender2, &point3DQue);
	pthread_create(&ReceiverThread, NULL, Receiver, &point3DQue);
	
	for(;;)
	sleep(1);
	pthread_exit(NULL);
	

	

	return 0;
}
