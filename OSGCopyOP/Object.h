

#ifndef OSG_OBJECT
#define OSG_OBJECT 1

#include "OSGreference.h"
#include "CopyOp.h"
#include <iostream>

/** Base class/standard interface for objects which require IO support,
    cloning and reference counting.
    Based on GOF Composite, Prototype and Template Method patterns.
*/
class  Object : public Referenced
{
    public:


        /** Construct an object. Note Object is a pure virtual base class
            and therefore cannot be constructed on its own, only derived
            classes which override the clone and className methods are
            concrete classes and can be constructed.*/
        inline Object():Referenced(),_dataVariance(UNSPECIFIED)  {}

        inline explicit Object(bool threadSafeRefUnref):Referenced(threadSafeRefUnref),_dataVariance(UNSPECIFIED) {}

        /** Copy constructor, optional CopyOp object can be used to control
          * shallow vs deep copying of dynamic data.*/
        Object(const Object&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        /** Clone the type of an object, with Object* return type.
            Must be defined by derived classes.*/
        virtual Object* cloneType() const = 0;

        /** Clone an object, with Object* return type.
            Must be defined by derived classes.*/
        virtual Object* clone(const CopyOp&) const = 0;

        virtual bool isSameKindAs(const Object*) const { return true; }


        /** return the name of the object's library. Must be defined
            by derived classes. The OpenSceneGraph convention is that the
            namespace of a library is the same as the library name.*/
        virtual const char* libraryName() const = 0;

        /** return the name of the object's class type. Must be defined
            by derived classes.*/
        virtual const char* className() const = 0;

        /** return the compound class name that combines the library name and class name.*/
        std::string getCompoundClassName() const { return std::string(className()); }


        /** Convert 'this' into a Node pointer if Object is a Node, otherwise return 0.
          * Equivalent to dynamic_cast<Node*>(this).*/
        virtual Node* asNode() { return 0; }

        /** convert 'const this' into a const Node pointer if Object is a Node, otherwise return 0.
          * Equivalent to dynamic_cast<const Node*>(this).*/
        virtual const Node* asNode() const { return 0; }

        /** Set whether to use a mutex to ensure ref() and unref() are thread safe.*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

        /** Set the name of object using C++ style string.*/
        virtual void setName( const std::string& name ) { _name = name; }

        /** Set the name of object using a C style string.*/
        inline void setName( const char* name )
        {
            if (name) setName(std::string(name));
            else setName(std::string());
        }

        /** Get the name of object.*/
        inline const std::string& getName() const { return _name; }


        enum DataVariance
        {
            DYNAMIC,
            STATIC,
            UNSPECIFIED
        };

        /** Set the data variance of this object.
           * Can be set to either STATIC for values that do not change over the lifetime of the object,
           * or DYNAMIC for values that vary over the lifetime of the object. The DataVariance value
           * can be used by routines such as optimization codes that wish to share static data.
           * UNSPECIFIED is used to specify that the DataVariance hasn't been set yet. */
        inline void setDataVariance(DataVariance dv) { _dataVariance = dv; }

        /** Get the data variance of this object.*/
        inline DataVariance getDataVariance() const { return _dataVariance; }

        /** Compute the DataVariance based on an assessment of callback etc.*/
        virtual void computeDataVariance() {}



        /** Resize any per context GLObject buffers to specified size. */
        virtual void resizeGLObjectBuffers(unsigned int /*maxSize*/) {}

    protected:

        /** Object destructor. Note, is protected so that Objects cannot
            be deleted other than by being dereferenced and the reference
            count being zero (see osg::Referenced), preventing the deletion
            of nodes which are still in use. This also means that
            Nodes cannot be created on stack i.e Node node will not compile,
            forcing all nodes to be created on the heap i.e Node* node
            = new Node().*/
        virtual ~Object();

        std::string _name;
        DataVariance _dataVariance;


    private:

        /** disallow any copy operator.*/
        Object& operator = (const Object&) { return *this; }
};

template<typename T>
T* clone(const T* t, const CopyOp& copyop=CopyOp::SHALLOW_COPY)
{
    if (t)
    {
        ref_ptr<Object> obj = t->clone(copyop);

        T* ptr = dynamic_cast<T*>(obj.get());
        if (ptr)
        {
            obj.release();
            return ptr;
        }
        else
        {
            std::cout<<"Warning: osg::clone(const T*, osg::CopyOp&) cloned object not of type T, returning NULL."<<std::endl;
            return 0;
        }
    }
    else
    {
        std::cout<<"Warning: osg::clone(const T*, osg::CopyOp&) passed null object to clone, returning NULL."<<std::endl;
        return 0;
    }
}

template<typename T>
T* cloneType(const T* t)
{
    if (t)
    {
        osg::ref_ptr<osg::Object> obj = t->cloneType();

        T* ptr = dynamic_cast<T*>(obj.get());
        if (ptr)
        {
            obj.release();
            return ptr;
        }
        else
        {
            OSG_WARN<<"Warning: osg::cloneType(const T*) cloned object not of type T, returning NULL."<<std::endl;
            return 0;
        }
    }
    else
    {
        OSG_WARN<<"Warning: osg::cloneType(const T*) passed null object to clone, returning NULL."<<std::endl;
        return 0;
    }
}


#endif

