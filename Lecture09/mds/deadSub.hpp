#ifndef DEADSUB_HPP_
#define DEADSUB_HPP_

#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <Publisher.hpp>
#include "SubscriberHelper.hpp"


/**
 * class Subsciber
 */
class DeadSub : public osapi::ThreadFunctor
{
public:
  enum { MAX_MSG_COUNT = 10 };
  DeadSub(unsigned int subId);
  ~DeadSub();

protected:
  // The subscription it self is missing and os is the unsubscription - Where will you put these?
  void handleMsgIdHello(HelloMsg* hm);
  void handleMsg(unsigned long id, osapi::Message* msg);
  virtual void run();

  bool                 running_;
  osapi::MsgQueue      mq_;
  SubscriberHelper	   subH_;
  SubscriberHelper	   subH2_;

private:
  enum {
    ID_TERMINATE,
    ID_HELLO 
  };
  unsigned int subId_;
};

#endif