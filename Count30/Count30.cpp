/***************************************************
*
*
*
*
****************************************************/

#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

bool finish =false;


std::vector<int> CalculateNearestWinPoint(int iOri)
{
	std::vector<int>  VecI;

	iOri = iOri -1;
	VecI.push_back(iOri);

	while(iOri-4>0)
	{
		iOri = iOri -4 ;
		VecI.push_back(iOri);
	}
	return VecI;
}


void catchNearestWinPoint(std::vector<int> vi,bool finish)
{
	std::cout<<"the nearest win point is  "<<*(vi.end()-1)<<std::endl;
	vi.pop_back();
	//std::cout<<"user,  pls input you number "<<std::endl;

	return;
}

void calculaterBestReply(std::vector<int>& userInput,std::vector<int>& PointList)
{
	int iMax= userInput[userInput.size()-1];

	//for(std::vector<int>::iterator it = PointList.end(); it != PointList.begin(); --it)
	//{
	//	/* std::cout << *it; ... */
	//	if(*it>iMax)
	//	{
	//		std::cout<<"nearest winpoint is "<<*it<<std::endl;
	//	}
	//}

	//for (unsigned i = PointList.size()-1; i-- > 0; )
	for (int i = PointList.size()-1; i >= 0; i-- )
	{
		if(PointList[i]>iMax)
		{
			// mean already find nearest win point 

			//std::cout<<"nearest winpoint is "<<PointList[i]<<std::endl;
			
			
			int iMaxTryingTime =0;
			while ((iMax<PointList[i])&&(iMaxTryingTime<3))
			{
				std::cout<<++iMax<<' ';
				iMaxTryingTime++;

			}
			std::cout<<std::endl;

			if(iMax==PointList[0])
			{
				std::cout<<"robot win!"<<std::endl;
				finish = true;
			}
			
			return;
		}
	}
	std::cout<<"robot lose!"<<std::endl;
	finish = true;
	return;
}

void main()
{
    //std::string s;

    //std::getline( std::cin, s );

    //std::istringstream is( s );

    //std::vector<int> v( ( std::istream_iterator<int>( is ) ), std::istream_iterator<int>() );

    //for ( int x : v) std::cout << x << ' ';
    //std::cout << std::endl;

	int iPurpose;
	int iInterval;
	int userInput;
	bool FirstReachLose;
	std::string sSingal;
	char c1;

	//bool finish =false;

	std::cout<<"pls input purpose number\t"<<std::endl;
	std::cin>>iPurpose;

	std::cout<<"pls input interval counter"<<std::endl;
	std::cin>>iInterval;
	
	std::cout<<"first reach mean l ? (y or n)"<<std::endl;
	std::cin>>c1;


	if(c1=='y')
		FirstReachLose=true;
	else
		FirstReachLose =false;

	std::vector<int> iNearestWinPointList = CalculateNearestWinPoint(iPurpose);
	
	//std::cout<<"The nearest win point of number "<<iPurpose<<" is : "<<std::endl;
	//for(auto i = iNearestWinPointList.begin();i!=iNearestWinPointList.end();++i)
	//		std::cout<<*i<<std::endl;
	while (!finish)
	{
		std::cout<<"pls input one or multi number"<<std::endl;

		//std::cin>>userInput;

		//FirstReachLose=true;

		std::string s;

		std::getline( std::cin, s );

		std::istringstream is( s );

		std::vector<int> v( ( std::istream_iterator<int>( is ) ), std::istream_iterator<int>() );

		if (v.size()<=0)
			continue;
		else
		{

			calculaterBestReply(v,iNearestWinPointList);
		}

		//for ( int x : v) std::cout << x << ' ';
		//std::cout << std::endl;
		//}
	
	}

	getchar();

	//while(!finish)
	//{
	//	catchNearestWinPoint(iNearestWinPointList,finish);
	//}

	
}