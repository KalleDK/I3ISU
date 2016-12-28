#include <Publisher.hpp>
#include <MessageDistributionSystem.hpp>
#include <osapi/Log.hpp>

static const int MAX_QUEUE_SIZE=10;

const std::string HELLO_MSG = "Hello_Msg";
const std::string TERMINATE_MSG = "Terminate_Msg";

Publisher::Publisher()
  : running_(true),
    mq_(MAX_QUEUE_SIZE),
    timer_(osapi::createNewTimer(&mq_, ID_TIME_OUT)),
	timer2_(osapi::createNewTimer(&mq_, ID_TIME_OUT_TERMINATOR))
{
  OSAPI_LOG_DBG("Creating publisher with associated timer...");
}

Publisher::~Publisher()
{
  delete timer_;
  delete timer2_;
  mq_.send(ID_TERMINATE);
}


void Publisher::handleMsgIdTimeOut()
{
  OSAPI_LOG_DBG("Got timeout, publishing message and rearming...");
  /************************************************/
  /************************************************/
  /* Write the necessary code to publish an event */
  /************************************************/
  /************************************************/
  HelloMsg* sendme = new HelloMsg;
  sendme->data_ = "Hej fra Publisher";
  MessageDistributionSystem::getInstance().notify(HELLO_MSG, sendme);
  timer_->reArm(); // Timeout in TIMEOUT msec
}

void Publisher::handleMsgIdTimeOutTerminator()
{
  OSAPI_LOG_DBG("Got timeout, publishing message and rearming...");
  
  TerminateMsg* sendme = new TerminateMsg;
  MessageDistributionSystem::getInstance().notify(TERMINATE_MSG, sendme);
  OSAPI_LOG_DBG("Done notifying reArming timer");
//  timer2_->reArm(); // Timeout in TIMEOUT msec
  OSAPI_LOG_DBG("I am out of the terminator");
}

void Publisher::handleMsg(unsigned long id, osapi::Message* msg)
{
  switch(id)
  {
    case ID_TIME_OUT:
      handleMsgIdTimeOut();
      break;
	  
    case ID_TIME_OUT_TERMINATOR:
      handleMsgIdTimeOutTerminator();
      break;
	  
    case ID_TERMINATE:
      running_ = false;
      break;

    default:
      OSAPI_LOG_DBG("Arg, got unknown event...");
      break;
  }
  
}


void Publisher::run()
{
  OSAPI_LOG_DBG("Preparing for loop, arming timer...");
  timer_->arm(TIMEOUT);
  timer2_->arm(TIMEOUT*10);
  while(running_)
  {
    unsigned long id;
    osapi::Message* m = mq_.receive(id);
    handleMsg(id, m);
    delete m;
  }

  OSAPI_LOG_DBG("Ensuring timers are stopped...");
  timer_->disArm();

  OSAPI_LOG_DBG("Thread terminating...");
}


