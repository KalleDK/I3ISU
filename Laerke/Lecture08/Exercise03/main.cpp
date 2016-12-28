#include <iostream>
#include <string>
#include "SmartPointer.hpp"

int main(int argc, char* argv[]){
	std::cout << "Vi opretter sp1 og sp2 som int" << std::endl; 
	SmartPointer<int> sp1(new int(1));
	SmartPointer<int> sp2(new int(2));
	
	std::cout << "sp1: "<< *sp1.get() << " er oprettet: count" << sp1.getCount() << std::endl;
	std::cout << "sp2: "<< *sp2.get() << " er oprettet: count" << sp2.getCount() << std::endl << std::endl;
	
	//Vi tester assignement operatoren
	std::cout << "Vi sætter sp2 = sp1," << std::endl;
	sp2 = sp1;
	std::cout << "sp1 har int: "<< *sp1.get() << ": count" << sp1.getCount() <<  std::endl;
	std::cout << "sp2 har int: "<< *sp2.get() << ": count" << sp1.getCount() << std::endl <<  std::endl;
	
	{
		//Vi tester copy constuctoren 
		std::cout << "Vi opretter sp3(sp1) med copy constructoren i {}." << endl;
        SmartPointer<int> sp3(sp1);
        std::cout << "sp3 oprettet, har int: " << *sp3.get() << ": count" << sp3.getCount() << endl << std::endl;
	}
	
	//Vi tester destructor 
	std::cout << "Udenfor {}" << endl;
	std::cout << "sp1: "<< *sp1.get() << " har: count" << sp1.getCount() << std::endl;
}