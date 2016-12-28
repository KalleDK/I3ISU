#ifndef SCOPEDLOCKER_HPP_
#define SCOPEDLOCKER_HPP_


class ScopedLocker{
public:
    ScopedLocker(pthread_mutex_t & m) : mtx(m){
        pthread_mutex_lock(&mtx);
    }
    ~ScopedLocker(){
        pthread_mutex_unlock(&mtx);
    }
private:
    pthread_mutex_t & mtx;
};

#endif