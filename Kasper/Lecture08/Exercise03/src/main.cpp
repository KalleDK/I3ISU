
#include <iostream>
#include "SmartString.hpp"

int main ( int argc , char * argv [])
{
	SmartString<int> ss( new int (20));
//	std::cout << " String length : " << ss->length() << std::endl;

//	if (ss->find("world") != std::string::npos)
		std::cout << " The 'ss' string does contain 'world' " << std :: endl ;
//	else
		std::cout << " The 'ss' string does NOT contain 'world' " << std::endl ;

	SmartString<int> ss2 = ss; // <- Deliberately why ? What happens ?
	SmartString<int> ss3(ss);
	
	std::cout << *ss2 << std::endl;
}