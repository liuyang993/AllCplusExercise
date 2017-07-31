#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <regex>


  std::vector<std::string>
  resplit(const std::string & s, std::string rgx_str = "\\s+") {


      std::vector<std::string> elems;

      std::regex rgx (rgx_str);

      std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
      std::sregex_token_iterator end;

      while (iter != end)  {
          //std::cout << "S43:" << *iter << std::endl;
          elems.push_back(*iter);
          ++iter;
      }

      return elems;

  }

void main()
{
	std::string line;
	int iCorrectNumber =0;
	while ( std::getline(std::cin, line) ) {
		//std::cout<<line<<std::endl;
		int iSinbel = line.find("?");
		if(iSinbel>0)
		{
			std::cout<<"exist ? "<<std::endl;
			continue;
		}
		//  split string 

		//std::regex rgx("[\\+\\-\\=]");
		//std::sregex_token_iterator iter(line.begin(),
		//	line.end(),
		//	rgx,
		//	-1);
		//std::sregex_token_iterator end;
		//for ( ; iter != end; ++iter)
		//	std::cout << *iter << '\n';

		std::vector<std::string> v222 = resplit(line, "[\\+\\-\\=]");

		if(    (atoi(v222[0].c_str()) + atoi(v222[1].c_str()) == atoi(v222[2].c_str())) || (atoi(v222[0].c_str()) - atoi(v222[1].c_str()) == atoi(v222[2].c_str()))  )
			iCorrectNumber++;


	}
	std::cout<<"correct is "<<iCorrectNumber<<std::endl;
	getchar();

}


