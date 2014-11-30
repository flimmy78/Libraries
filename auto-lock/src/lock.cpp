#include "lock.h"

CMutex::CMutex()
{
    pthread_mutex_init(&m_mutex, NULL);
}

CMutex::~CMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void CMutex::Lock() const
{
    pthread_mutex_lock(&m_mutex);
}

void CMutex::Unlock() const
{
    pthread_mutex_unlock(&m_mutex);
}

CAutoLock::CAutoLock(const ILock& m) : m_lock(m)
{
    m_lock.Lock();
}

CAutoLock::~CAutoLock()
{
    m_lock.Unlock();
}