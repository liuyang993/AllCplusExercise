#include "CopyOP.h"

#define COPY_OP( TYPE, FLAG ) \
TYPE* CopyOp::operator() (const TYPE* obj) const \
{ \
    if (obj && _flags&FLAG) \
        return osg::clone(obj, *this); \
    else \
        return const_cast<TYPE*>(obj); \
}

COPY_OP( Drawable,DEEP_COPY_DRAWABLES )

Referenced* CopyOp::operator() (const Referenced* ref) const
{
    return const_cast<Referenced*>(ref);
}

Node* CopyOp::operator() (const Node* node) const
{
    if (!node) return 0;

    const Drawable* drawable = node->asDrawable();
    if (drawable) return operator()(drawable);
    else if (_flags&DEEP_COPY_NODES) return osg::clone(node, *this);
    else return const_cast<Node*>(node);
}

