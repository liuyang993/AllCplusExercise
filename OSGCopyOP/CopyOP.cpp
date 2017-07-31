#include "CopyOP.h"
#include "Object.h"
#include "Node.h"
#include "OSGRef_ptr.h"

#define COPY_OP( TYPE, FLAG ) \
TYPE* CopyOp::operator() (const TYPE* obj) const \
{ \
    if (obj && _flags&FLAG) \
        return clone(obj, *this); \
    else \
        return const_cast<TYPE*>(obj); \
}

//COPY_OP( Node,DEEP_COPY_NODES )
COPY_OP( Object,DEEP_COPY_OBJECTS )

Referenced* CopyOp::operator() (const Referenced* ref) const
{
    return const_cast<Referenced*>(ref);
}

Node* CopyOp::operator() (const Node* node) const
{
    if (!node) return 0;

    const Node* drawable = node->asNode();
    if (drawable) return operator()(drawable);
    else if (_flags&DEEP_COPY_NODES) return clone(node, *this);
    else return const_cast<Node*>(node);
}

