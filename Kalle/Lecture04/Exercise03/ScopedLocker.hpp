#include <pthread.h>

class ScopedLocker {
public:
	ScopedLocker(pthread_mutex_t* mtx) {
		this->mtx = mtx;
		pthread_mutex_lock(this->mtx);
	};
	~ScopedLocker() {
		pthread_mutex_unlock(this->mtx);
	};
private:
	pthread_mutex_t* mtx;

};
