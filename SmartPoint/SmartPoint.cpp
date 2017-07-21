#include<iostream>
#include<assert.h>
#include "OgreSharedPtr.h"
#include "OSGRef_ptr.h"
#include "OSGreference.h"

class CA : public Referenced
{
public:
	CA() { i  =0; };
	virtual ~CA() {};
	int i;
};

void WildPointer()
{
	CA *c1 = new CA();
	c1->i=1024;
	CA *c2 = c1;

	delete c1;
	c1=nullptr;

	CA *c3;
	//assert(c2!=NULL);
	int j  =(*c2).i;          // now c2  become wild pointer
	//j  =(*c3).i;
}

void UseOgreSharedPointer()
{
	CA *c1 = new CA();
	SharedPtr<CA> SharedC1 ;
	SharedC1.bind(c1);
	CA *c2 = c1;


	return;
}

void UseOSGRefPointer()
{

	ref_ptr<CA> SharedC1 = new CA();
		CA *c2 = new CA();

	//ref_ptr<CA> SharedC2 = SharedC1 ;
	//delete c1;
	/*CA *c2 = c1;*/

	return;

}

void main()
{
	WildPointer();
	UseOgreSharedPointer();

	UseOSGRefPointer();


	return;
}