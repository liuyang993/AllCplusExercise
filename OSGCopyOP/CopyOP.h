#ifndef OSG_COPYOP
#define OSG_COPYOP 1

class Referenced;
class Node;
class Drawable;
class Object;

class  CopyOp
{

    public:

        enum Options
        {
            SHALLOW_COPY                = 0,
            DEEP_COPY_OBJECTS           = 1<<0,
            DEEP_COPY_NODES             = 1<<1,
            DEEP_COPY_DRAWABLES         = 1<<2,
            DEEP_COPY_STATESETS         = 1<<3,
            DEEP_COPY_STATEATTRIBUTES   = 1<<4,
            DEEP_COPY_TEXTURES          = 1<<5,
            DEEP_COPY_IMAGES            = 1<<6,
            DEEP_COPY_ARRAYS            = 1<<7,
            DEEP_COPY_PRIMITIVES        = 1<<8,
            DEEP_COPY_SHAPES            = 1<<9,
            DEEP_COPY_UNIFORMS          = 1<<10,
            DEEP_COPY_CALLBACKS         = 1<<11,
            DEEP_COPY_USERDATA          = 1<<12,
            DEEP_COPY_ALL               = 0x7FFFFFFF
        };

        typedef unsigned int CopyFlags;

        inline CopyOp(CopyFlags flags=SHALLOW_COPY):_flags(flags) {}
        virtual ~CopyOp() {}

        void setCopyFlags(CopyFlags flags) { _flags = flags; }
        CopyFlags getCopyFlags() const { return _flags; }

        virtual Referenced*     operator() (const Referenced* ref) const;
		virtual Node*           operator() (const Node* node) const;
        virtual Object*         operator() (const Object* obj) const;

    protected:

        CopyFlags _flags;
};



#endif