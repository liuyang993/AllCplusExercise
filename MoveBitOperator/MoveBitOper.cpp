#include <iostream>

void main()
{
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

	std::cout<<DEEP_COPY_OBJECTS<<std::endl;
	std::cout<<DEEP_COPY_NODES<<std::endl;
	std::cout<<DEEP_COPY_DRAWABLES<<std::endl;
	std::cout<<DEEP_COPY_USERDATA<<std::endl;
	std::cout<<DEEP_COPY_ALL<<std::endl;
	

	
	getchar();

	return;
}