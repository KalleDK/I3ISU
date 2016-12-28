#pragma once
#include <pthread.h>
#include <queue>
#include "Message.hpp"

struct Item
{
	unsigned long id_;
	Message* msg_;
};

class MsgQueue
{
public:
	MsgQueue(unsigned long maxSize = 10){
		maxSize_ = maxSize;
	};
	void send(unsigned long id, Message* msg = NULL){
		pthread_mutex_lock(&msgMtx);
		while(msgQue_.size() >= maxSize_){
			  pthread_cond_wait(&isFull, &msgMtx);
		}
	//	std::cout << "IN: B\n";
		struct Item put = {.id_ = id, .msg_ = msg};
		msgQue_.push(put);
	//	std::cout << "In: " << msgQue_.size() << "\n";
		pthread_cond_signal(&isEmpty);
		pthread_mutex_unlock(&msgMtx);
	};
	Message* receive(unsigned long& id){
		pthread_mutex_lock(&msgMtx);
		Message* msg;
		while(msgQue_.empty()){
			pthread_cond_wait(&isEmpty, &msgMtx);
		//	std::cout << "I was blocked receiver\n";
		}
	//	std::cout << "OUT: B\n";
		msg = msgQue_.front().msg_;
		id = msgQue_.front().id_;
		msgQue_.pop();
	//	std::cout << "Out: " << msgQue_.size() << "\n";
		pthread_cond_signal(&isFull);
		pthread_mutex_unlock(&msgMtx);
		return msg;
	};
	~MsgQueue(){};
private:
	unsigned long maxSize_;
	pthread_mutex_t msgMtx = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t isFull = PTHREAD_COND_INITIALIZER;
	pthread_cond_t isEmpty = PTHREAD_COND_INITIALIZER;
	std::queue<Item> msgQue_;
	
};
