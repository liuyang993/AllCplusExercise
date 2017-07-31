#include "CopyOp.h"
#include "OSGRef_ptr.h"
#include <iostream>
#include "Node.h"
#include <map>


class MyCopyOp : public CopyOp
{
    public:

        inline MyCopyOp(CopyFlags flags=SHALLOW_COPY):
            CopyOp(flags),
            _indent(0),
            _step(4) {}

        inline void moveIn() const { _indent += _step; }
        inline void moveOut() const { _indent -= _step; }
        inline void writeIndent() const
        {
            for(int i=0;i<_indent;++i) std::cout << " ";
        }

        virtual Referenced*     operator() (const Referenced* ref) const
        {
            writeIndent(); std::cout << "copying Referenced "<<ref<<std::endl;
            moveIn();
            Referenced* ret_ref = CopyOp::operator()(ref);
            moveOut();
            return ret_ref;
        }

        virtual Object*         operator() (const Object* obj) const
        {
            writeIndent(); std::cout << "copying Object "<<obj;
            if (obj) std::cout<<" "<<obj->className();
            std::cout<<std::endl;
            moveIn();
            Object* ret_obj = CopyOp::operator()(obj);
            moveOut();
            return ret_obj;
        }

        virtual Node*           operator() (const Node* node) const
        {
            writeIndent(); std::cout << "copying Node "<<node;
            if (node) std::cout<<" "<<node->className()<<" '"<<node->getName()<<"'";
            std::cout<<std::endl;
            moveIn();
            Node* ret_node = CopyOp::operator()(node);
            moveOut();
            return ret_node;
        }

    protected:

        // must be mutable since CopyOp is passed around as const to
        // the various clone/copy constructors.
        mutable int _indent;
        mutable int _step;
};

// this CopyOp class will preserve the multi-parent structure of the copied
// object, instead of expanding it into a tree. Works with the
// DEEP_COPY_NODES flag.
class GraphCopyOp : public CopyOp
{
    public:

        inline GraphCopyOp(CopyFlags flags=SHALLOW_COPY):
            CopyOp(flags) { _nodeCopyMap.clear();}

        virtual Node* operator() (const Node* node) const
        {
            if (node && _flags&DEEP_COPY_NODES)
            {

                return dynamic_cast<Node*>( node->clone(*this) );
            }
            else
                return const_cast<Node*>(node);
        }

    protected:

        // must be mutable since CopyOp is passed around as const to
        // the various clone/copy constructors.
        mutable std::map<const Node*,Node*> _nodeCopyMap;

};


int main()
{
	ref_ptr<Node> rootnode = new Node();
    if (!rootnode)
    {
        std::cout<<"Please specify a model filename on the command line."<<std::endl;
        return 1;
    }

// -------------    Start of copy specific code -------------------------------------------------------

    // do a deep copy, using MyCopyOp to reveal whats going on under the hood,
    // in your own code you'd typically just use the basic osg::CopyOp something like
    ref_ptr<Node> mycopy = dynamic_cast<Node*>(rootnode->clone(CopyOp::DEEP_COPY_ALL));
    std::cout << "Doing a deep copy of scene graph"<<std::endl;

    // note, we need the dyanmic_cast because MS Visual Studio can't handle covarient
    // return types, so that clone has return just Object*.  bahh hum bug
    //ref_ptr<Node> deep_copy = dynamic_cast<Node*>(rootnode->clone(MyCopyOp(osg::CopyOp::DEEP_COPY_ALL)));

    //std::cout << "----------------------------------------------------------------"<<std::endl;

    // do a graph preserving deep copy.
    //std::cout << "Doing a graph preserving deep copy of scene graph nodes"<<std::endl;
    //ref_ptr<Node> graph_copy = dynamic_cast<Node*>(rootnode->clone(GraphCopyOp(osg::CopyOp::DEEP_COPY_NODES)));


    // do a shallow copy.
    std::cout << "Doing a shallow copy of scene graph"<<std::endl;
    ref_ptr<Node> shallow_copy = dynamic_cast<Node*>(rootnode->clone(MyCopyOp(CopyOp::SHALLOW_COPY)));



	getchar();

	return 0;

}