#ifndef NH_Lock_H
#define NH_Lock_H

#include <pthread.h>

//interface
class ILock
{
public:
    ILock() {}
    virtual ~ILock() {}
 
    virtual void Lock() const = 0;
    virtual void Unlock() const = 0;
};
 
//mutex class
class CMutex : public ILock
{
public:
    CMutex();
    ~CMutex();

    virtual void Lock() const;
    virtual void Unlock() const;

private:
    mutable pthread_mutex_t m_mutex;
};

//auto lock
class CAutoLock
{
public:
    CAutoLock(const ILock&);
    ~CAutoLock();

private:
    const ILock& m_lock;
};

#endif //NH_Lock_H