
#include "Object.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Object
//
Object::Object(const Object& obj,const CopyOp& copyop):
    Referenced(),
    _name(obj._name),
    _dataVariance(obj._dataVariance)
{

}

Object::~Object()
{
  
}


void Object::setThreadSafeRefUnref(bool threadSafe)
{
    Referenced::setThreadSafeRefUnref(threadSafe);
}

