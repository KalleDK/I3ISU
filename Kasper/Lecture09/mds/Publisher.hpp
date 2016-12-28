#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include <osapi/MsgQueue.hpp>
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Timer.hpp>

/** Global message Hello
 */
struct HelloMsg : public osapi::Message
{
  std::string data_;
};
extern const std::string HELLO_MSG;

struct TerminateMsg : public osapi::Message
{
  
};
extern const std::string TERMINATE_MSG;


class Publisher : public osapi::ThreadFunctor
{
public:
  Publisher();
  ~Publisher();
private:
  void handleMsgIdTimeOut();
  void handleMsgIdTimeOutTerminator();
  void handleMsg(unsigned long id, osapi::Message* msg);
  virtual void run();
  
  bool                 running_;
  osapi::MsgQueue      mq_;
  osapi::ITimerId*     timer_;
  osapi::ITimerId*     timer2_;
  
  enum { ID_TIME_OUT,
		 ID_TIME_OUT_TERMINATOR,
         ID_TERMINATE 
  };

  enum { TIMEOUT = 1000 };
};


#endif
