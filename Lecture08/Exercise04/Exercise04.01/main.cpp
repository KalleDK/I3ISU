#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

int main(int argc, char* argv[]){
	std::cout << "Vi opretter sp1 og sp2 som int" << std::endl; 
	boost::shared_ptr<std::string> sp1(new std:: string("SmartString 1"));
	boost::shared_ptr<std::string> sp2(new std:: string("SmartString 2"));
	
	std::cout << "sp1: "<< *sp1 << " er oprettet: count " << sp1.use_count() << std::endl;
	std::cout << "sp2: "<< *sp2 << " er oprettet: count " << sp2.use_count() << std::endl << std::endl;
	
	//Vi tester assignement operatoren
	std::cout << "Vi sætter sp2 = sp1," << std::endl;
	sp2 = sp1;
	std::cout << "sp1 har string: "<< *sp1 << ": count" << sp1.use_count() << std::endl;
	std::cout << "sp2 har string: "<< *sp2 << ": count" << sp1.use_count() << std::endl <<  std::endl;
	
	{
		//Vi tester copy constuctoren 
		std::cout << "Vi opretter sp3(sp1) med copy constructoren i {}." << std::endl;
        boost::shared_ptr<std::string>  sp3(sp1);
        std::cout << "sp3 oprettet, har string: " << *sp3 << ": count" << sp3.use_count() << std::endl << std::endl;
	}
	
	//Vi tester destructor 
	std::cout << "Udenfor {}" << std::endl;
	std::cout << "sp1: "<< *sp1 << " har: count" << sp1.use_count() << std::endl;
}