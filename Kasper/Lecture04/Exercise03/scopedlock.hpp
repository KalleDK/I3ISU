#include <pthread.h>

class scopedLocker
{
	public:
	scopedLocker(pthread_mutex_t &mtx) : scpMtx(mtx)
	{
		pthread_mutex_lock(&scpMtx);
	};
	~scopedLocker()
	{
		pthread_mutex_unlock(&scpMtx);
	};
	

	private:
	pthread_mutex_t & scpMtx;
};
