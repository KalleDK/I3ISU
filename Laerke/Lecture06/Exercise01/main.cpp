#include <iostream> 
#include <stdlib.h> 
#include "Message.hpp"
#include "MsgQueue.h"

unsigned long sleep_time = 1;

struct Point3D : public Message
{
  int x;
  int y;
  int z;
}

static void* SenderFUNC(void *shared){
  struct Point3D min_point;
  
  
  min_point.x = rand() % 100;
  min_point.y = rand() % 100;
  min_point.z = rand() % 100;
  
  sleep(sleep_time);
  
}

static void* ReceiverFUNC(void *shared){
   
}

int main(int argc, char* argv[])
{
  pthread_t Sender;
  pthread_t Receiver;
  
  MsgQueu Mq(100);
  
  pthread_create(&Sender, NULL, SenderFUNC(), &Mq);
  pthread_create(&Receiver, NULL, ReceiverFUNC, &Mq);
}