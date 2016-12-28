#pragma once
#include <deque>
#include <pthread.h>
#include <memory>
#include "Message.hpp"

struct Item
{
	unsigned long			id_;
	Message*			msg_;
};

class MsgQueue
{
public :
	MsgQueue ( unsigned long maxSize ) ; 
	void send ( unsigned long id , Message* msg = NULL ) ;
	Message * receive ( unsigned long & id ) ;
	virtual ~MsgQueue () ;
private :
	std::deque<Item>	q_;
	unsigned long 		maxSize_;
	pthread_mutex_t 	m_ 		= PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t 		not_full_cond_ 	= PTHREAD_COND_INITIALIZER;
	pthread_cond_t 		not_empty_cond_ = PTHREAD_COND_INITIALIZER;
};
