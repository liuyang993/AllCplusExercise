

#ifndef OSG_NODE
#define OSG_NODE 1

#include "Object.h"
#include <iostream>
#include <string>
#include <vector>


// forcing declare classes to enable declaration of as*() methods.

class Node;

/** A vector of Nodes pointers which is used to describe the path from a root node to a descendant.*/
typedef std::vector< Node* > NodePath;

/** A vector of NodePath, typically used to describe all the paths from a node to the potential root nodes it has.*/
typedef std::vector< NodePath > NodePathList;

/** META_Node macro define the standard clone, isSameKindAs, className
  * and accept methods.  Use when subclassing from Node to make it
  * more convenient to define the required pure virtual methods.*/
#define META_Node(library,name) \
        virtual osg::Object* cloneType() const { return new name (); } \
        virtual osg::Object* clone(const osg::CopyOp& copyop) const { return new name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* className() const { return #name; } \
        virtual const char* libraryName() const { return #library; } \
      


/** Base class for all internal nodes in the scene graph.
    Provides interface for most common node operations (Composite Pattern).
*/
class  Node : public Object
{
    public:

        /** Construct a node.
            Initialize the parent list to empty, node name to "" and
            bounding sphere dirty flag to true.*/
        Node();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Node(const Node&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        /** clone an object of the same type as the node.*/
        virtual Object* cloneType() const { return new Node(); }

        /** return a clone of a node, with Object* return type.*/
        virtual Object* clone(const CopyOp& copyop) const { return new Node(*this,copyop); }

        /** return true if this and obj are of the same kind of object.*/
        virtual bool isSameKindAs(const Object* obj) const { return dynamic_cast<const Node*>(obj)!=NULL; }

        /** return the name of the node's library.*/
        virtual const char* libraryName() const { return "osg"; }

        /** return the name of the node's class type.*/
        virtual const char* className() const { return "Node"; }

        /** Convert 'this' into a Node pointer if Object is a Node, otherwise return 0.
          * Equivalent to dynamic_cast<Node*>(this).*/
        virtual Node* asNode() { return this; }

        /** convert 'const this' into a const Node pointer if Object is a Node, otherwise return 0.
          * Equivalent to dynamic_cast<const Node*>(this).*/
        virtual const Node* asNode() const { return this; }

    protected:

        /** Node destructor. Note, is protected so that Nodes cannot
            be deleted other than by being dereferenced and the reference
            count being zero (see osg::Referenced), preventing the deletion
            of nodes which are still in use. This also means that
            Nodes cannot be created on stack i.e Node node will not compile,
            forcing all nodes to be created on the heap i.e Node* node
            = new Node().*/
        virtual ~Node();

};



#endif
