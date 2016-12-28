
#include <iostream>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Log.hpp>
#include <MessageDistributionSystem.hpp>

#include <Publisher.hpp>
#include <Subscriber.hpp>
#include <deadSub.hpp>

  


int main(int argc, char* argv[])
{
  OSAPI_LOG_DBG("Starting up...");
  MessageDistributionSystem::getInstance();
  Publisher p;
  osapi::Thread pTh(&p);

  Subscriber s1(1), s2(2);
  osapi::Thread s1Th(&s1);
  osapi::Thread s2Th(&s2);
  
  
  pTh.start();
  s1Th.start();
  s2Th.start();
  
 { 
	DeadSub ds(1);
	osapi::Thread dsTh(&ds);
	dsTh.start();
	dsTh.join();
  }
  

  /* Never stops - Why? */

  pTh.join();
  s1Th.join();
  s2Th.join();
}

