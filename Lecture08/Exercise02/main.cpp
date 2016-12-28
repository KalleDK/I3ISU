#include <iostream>
#include <string>
#include "SmartString.hpp"

int main(int argc, char* argv[]){
	std::cout << "Vi opretter ss1 og ss2" << std::endl; 
	SmartString ss1(new std:: string("SmartString 1"));
	SmartString ss2(new std:: string("SmartString 2"));
	
	std::cout << "ss1: "<< *ss1.get() << " er oprettet: count" << ss1.getCount() << std::endl;
	std::cout << "ss2: "<< *ss2.get() << " er oprettet: count" << ss2.getCount() << std::endl << std::endl;
	
	//Vi tester assignement operatoren
	std::cout << "Vi sætter ss2 = ss1," << std::endl;
	ss2 = ss1;
	std::cout << "ss1 har string: "<< *ss1.get() << ": count" << ss1.getCount() <<  std::endl;
	std::cout << "ss2 har string: "<< *ss2.get() << ": count" << ss1.getCount() << std::endl <<  std::endl;
	
	{
		//Vi tester copy constuctoren 
		std::cout << "Vi opretter ss3(ss1) med copyconstructoren i {}." << endl;
        SmartString ss3(ss1);
        std::cout << "ss3 oprettet, har string: " << *ss3.get() << ": count" << ss3.getCount() << endl << std::endl;
	}
	
	//Vi tester destructor 
	std::cout << "Udenfor {}" << endl;
	std::cout << "ss1: "<< *ss1.get() << " har: count" << ss1.getCount() << std::endl;
}