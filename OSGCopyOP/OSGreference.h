
#ifndef OSG_REFERENCED
#define OSG_REFERENCED 1


#if !defined(_OPENTHREADS_ATOMIC_USE_MUTEX)
# define _OSG_REFERENCED_USE_ATOMIC_OPERATIONS
#endif



// forward declare, declared after Referenced below.
//class DeleteHandler;
//class Observer;
//class ObserverSet;

/** template class to help enforce static initialization order. */
template <typename T, T M()>
struct depends_on
{
    depends_on() { M(); }
};

/** Base class for providing reference counted objects.*/
class  Referenced
{
    public:
        Referenced();

        /** Deprecated, Referenced is now always uses thread safe ref/unref, use default Refernced() constructor instead */
        explicit Referenced(bool threadSafeRefUnref);

        Referenced(const Referenced&);

        inline Referenced& operator = (const Referenced&) { return *this; }

        /** Deprecated, Referenced is always theadsafe so there method now has no effect and does not need to be called.*/
        virtual void setThreadSafeRefUnref(bool /*threadSafe*/) {}

        /** Get whether a mutex is used to ensure ref() and unref() are thread safe.*/
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
        bool getThreadSafeRefUnref() const { return true; }
#else
        bool getThreadSafeRefUnref() const { return _refMutex!=0; }
#endif

        /** Increment the reference count by one, indicating that
            this object has another pointer which is referencing it.*/
        long ref() const;

        /** Decrement the reference count by one, indicating that
            a pointer to this object is no longer referencing it.  If the
            reference count goes to zero, it is assumed that this object
            is no longer referenced and is automatically deleted.*/
        long unref() const;

        /** Decrement the reference count by one, indicating that
            a pointer to this object is no longer referencing it.  However, do
            not delete it, even if ref count goes to 0.  Warning, unref_nodelete()
            should only be called if the user knows exactly who will
            be responsible for, one should prefer unref() over unref_nodelete()
            as the latter can lead to memory leaks.*/
        long unref_nodelete() const;

        /** Return the number of pointers currently referencing this object. */
        inline int referenceCount() const { return _refCount; }



    protected:

        virtual ~Referenced();

        void signalObserversAndDelete(bool signalDelete, bool doDelete) const;

        void deleteUsingDeleteHandler() const;

#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)

        volatile long     _refCount;
#else

        mutable OpenThreads::Mutex*     _refMutex;

        mutable int                     _refCount;

#endif
};




// intrusive_ptr_add_ref and intrusive_ptr_release allow
// use of osg Referenced classes with boost::intrusive_ptr
inline void intrusive_ptr_add_ref(Referenced* p) { p->ref(); }
inline void intrusive_ptr_release(Referenced* p) { p->unref(); }



#endif
