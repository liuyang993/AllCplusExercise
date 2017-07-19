#include <iostream>
#include <vector>

std::vector<int> CalculateNearestWinPoint(int iOri)
{
	std::vector<int>  VecI;

	iOri = iOri -5;
	VecI.push_back(iOri);

	while(iOri-10>0)
	{
		iOri = iOri -10 ;
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


void main()
{
	int iPurpose;
	bool finish =false;

	std::cout<<"pls input purpose counter"<<std::endl;
	std::cin>>iPurpose;
	

	std::vector<int> iNearestWinPointList = CalculateNearestWinPoint(iPurpose);
	
	std::cout<<"The nearest win point of number "<<iPurpose<<" is : "<<std::endl;
	for(auto i = iNearestWinPointList.begin();i!=iNearestWinPointList.end();++i)
			std::cout<<*i<<std::endl;


	std::cout<<"pls input your number"<<std::endl;

	//while(!finish)
	//{
	//	catchNearestWinPoint(iNearestWinPointList,finish);
	//}


	std::cin;




}