#pragma once

#include <pthread.h>

class ScopedLock
{
public:
    ScopedLock(pthread_mutex_t & mutex):
        m_mutex(mutex)
    {
        pthread_mutex_lock(&m_mutex);
    }

    ~ScopedLock()
    {
        pthread_mutex_unlock(&m_mutex);
    }

private:
    pthread_mutex_t & m_mutex;
};
