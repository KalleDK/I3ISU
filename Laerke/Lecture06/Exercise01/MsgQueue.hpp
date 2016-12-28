#include "Message.hpp"
#include <queue>
#include <pthreads.h>

struct Item{
  unsigned long id_;
  Message* msg_;
}

pthread_cond_t send_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t receive_cond = PTHREAD_COND_INITIALIZER;

class MsgQueue
{
  public:
    MsgQueue(unsigned long maxSize) : maxSize_(maxSize)
    {
      mtx = PTHREAD_MUTEX_INITIALIZER;
    };
    
    void send(unsigned long id, Message* msg = NULL)
    {
      while(mq_.size() >= maxSize_){
	 pthread_cond_wait(&send_cond,&mtx);
      }
      pthread_cond_signal(&receive_cond);
    };
    
    Message* receive(unsigned long& id)
    {
      while(mq_.size() == 0){
	 pthread_cond_wait(&receive_cond,&mtx);
      }
      pthread_cond_signal(&send_cond);
    };
    
    ~MsgQueue();
  private:
    unsigned long maxSize_;
    pthread_mutex_t mtx_;
    queue<Item> mq_;
}