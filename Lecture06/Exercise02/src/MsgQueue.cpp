#include "MsgQueue.hpp"

MsgQueue::MsgQueue ( unsigned long maxSize ) : maxSize_(maxSize)  {
	m_						= PTHREAD_MUTEX_INITIALIZER;
	not_full_cond_		= PTHREAD_COND_INITIALIZER;
	not_empty_cond_	= PTHREAD_COND_INITIALIZER;
}

MsgQueue::~MsgQueue () {
	Item item;
	while (!q_.empty()) {
		item = q_.back();
		q_.pop_back();
		delete item.msg_;
	}
}

void MsgQueue::send ( unsigned long id , Message * msg) {
	pthread_mutex_lock(&m_);
	while(q_.size() >= maxSize_) {
		pthread_cond_wait(&not_full_cond_, &m_);
	}
	struct Item item;
	item.id_ = id;
	item.msg_ = msg;
	q_.push_front(item);
	pthread_cond_signal(&not_empty_cond_);
	pthread_mutex_unlock(&m_);
}

Message* MsgQueue::receive ( unsigned long& id )
{
	pthread_mutex_lock(&m_);
	while(q_.empty()) {
		pthread_cond_wait(&not_empty_cond_, &m_);
	}
	struct Item item = q_.back();
	q_.pop_back();
	pthread_cond_signal(&not_full_cond_);
	pthread_mutex_unlock(&m_);
	id = item.id_;
	return item.msg_;
}

