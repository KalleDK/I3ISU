#include <osapi/Log.hpp>
#include <MessageDistributionSystem.hpp>
#include <deadSub.hpp>

static const int MAX_QUEUE_SIZE=10;


DeadSub::DeadSub(unsigned int subId)
  :  mq_(MAX_QUEUE_SIZE), subH_(HELLO_MSG, &mq_, ID_HELLO), subH2_(TERMINATE_MSG, &mq_, ID_TERMINATE), subId_(subId)
{
  /*****************************************************/
  /*****************************************************/
  /* Write the necessary code to subscribe to an event */
  /*****************************************************/
  /*****************************************************/    
  OSAPI_LOG_DBG("Constructing deadsubs!");
  
}


DeadSub::~DeadSub()
{
  mq_.send(ID_TERMINATE);
}


void DeadSub::handleMsgIdHello(HelloMsg* hm)
{
  OSAPI_LOG_DBG("S(" << subId_ << ") The hello message contained: '" << hm->data_ << "'");

  /*******************************************************/
  /*******************************************************/
  /* Write the necessary code to unsubscribe to an event */
  /*******************************************************/
  /*******************************************************/    
  //MessageDistributionSystem::getInstance().unSubscribe(HELLO_MSG, &mq_, ID_HELLO);
  //subH_.unSubscribe();
}




void DeadSub::handleMsg(unsigned long id, osapi::Message* msg)
{
  switch(id)
  {
    case ID_HELLO:
      handleMsgIdHello(static_cast<HelloMsg*>(msg));
      break;
        
    case ID_TERMINATE:
	  running_ = false;
      OSAPI_LOG_DBG("S(" << subId_ << ") Got terminate signal");
      break;
  }
    
}


void DeadSub::run()
{
  OSAPI_LOG_DBG("Preparing for loop...");

  while(running_)
  {
    unsigned long id;
    osapi::Message* m = mq_.receive(id);
    handleMsg(id, m);
    delete m;
  }

  OSAPI_LOG_DBG("Thread terminating...");
}
