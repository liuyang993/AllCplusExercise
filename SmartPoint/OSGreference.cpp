
#include <stdlib.h>
#include "OSGreference.h"
#include <windows.h>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <set>

template<typename T>
struct ResetPointer
{
    ResetPointer():
        _ptr(0) {}

    ResetPointer(T* ptr):
        _ptr(ptr) {}

    ~ResetPointer()
    {
        delete _ptr;
        _ptr = 0;
    }

    inline ResetPointer& operator = (T* ptr)
    {
        if (_ptr==ptr) return *this;
        delete _ptr;
        _ptr = ptr;
        return *this;
    }

    void reset(T* ptr)
    {
        if (_ptr==ptr) return;
        delete _ptr;
        _ptr = ptr;
    }

    inline T& operator*()  { return *_ptr; }

    inline const T& operator*() const { return *_ptr; }

    inline T* operator->() { return _ptr; }

    inline const T* operator->() const   { return _ptr; }

    T* get() { return _ptr; }

    const T* get() const { return _ptr; }

    T* _ptr;
};


Referenced::Referenced():
    _refCount(0)
{
}

Referenced::Referenced(bool /*threadSafeRefUnref*/):
    _refCount(0)
{
}

Referenced::Referenced(const Referenced&):
    _refCount(0)
{
}


long Referenced::ref() const
{
    return InterlockedIncrement(&(LONG)_refCount);
}

long Referenced::unref() const
{
    long newRef;
    newRef = InterlockedDecrement(&(LONG)_refCount);
    bool needDelete = (newRef == 0);

    if (needDelete)
    {
        signalObserversAndDelete(true,true);
    }
    return newRef;
}


Referenced::~Referenced()
{
    if (_refCount>0)
    {
        std::cout<<"Warning: deleting still referenced object "<<this<<" of type '"<<typeid(this).name()<<"'"<<std::endl;
        std::cout<<"         the final reference count was "<<_refCount<<", memory corruption possible."<<std::endl;
    }
}

void Referenced::signalObserversAndDelete(bool signalDelete, bool doDelete) const
{

    if (doDelete)
    {
        if (_refCount!=0)
            std::cout<<"Warning Referenced::signalObserversAndDelete(,,) doing delete with _refCount="<<_refCount<<std::endl;

        else delete this;
    }
}

long Referenced::unref_nodelete() const
{
    return InterlockedDecrement(&(LONG)_refCount);
}

