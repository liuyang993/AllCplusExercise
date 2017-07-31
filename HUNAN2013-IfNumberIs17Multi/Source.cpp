#include <iostream>
#include <string>
#include <stdio.h>

int JudgeNumber(std::string sInt)
{
	//if(iInput<10)
	//	return 0;

	std::string sSubString = sInt.substr(0,sInt.size()-1);
	std::cout<<sSubString<<std::endl;

	std::string sTail = sInt.substr(sInt.size()-1,1);
	std::cout<<sTail<<std::endl;

	int iNumber = atoi(sSubString.c_str());
	int iTailNumber = atoi(sTail.c_str());

	int iTemp = iNumber - iTailNumber*5;



	if(iTemp%17 ==0)	
		return 1;
	else
		return 0 ;

}


void main()
{
	if (JudgeNumber("1111111111111111111111111111111111111") == 1)
		std::cout<<"Yes"<<std::endl;
	else
		std::cout<<"No"<<std::endl;
	getchar();
	return;
}