#include <iostream>
#include <stdio.h>

void main()
{
	int iOri = 0;
	printf("%d\n",iOri/3);  //shang
	printf("%d\n",iOri%3);  //yu  shu

	int iDrink = 0;

	/*getchar();*/
	
	int itemp = iOri/3 + iOri%3;
	iDrink = iOri/3;

	while(itemp >=3)
	{
		iDrink = iDrink + itemp/3;
		itemp = itemp/3 + itemp%3;
	}


	printf("final yu shu is %d\n",itemp);  //yu  shu

	if(itemp ==2)
		iDrink++;

	printf("final can drink %d\n",iDrink);  


	getchar();
	return;

}