#include <iostream>
#include <string>

using namespace std;

class SmartString {
	public:
		SmartString(string* str):str_(str){}
		
		~SmartString(){
			delete str_;
		}
		
		string* get(){
			return str_;
		}
		
		string *operator->(){
			return str_;
		}
		
		string &operator*(){
			return *str_;
		}
		
	private:
		SmartString(const SmartString & other){}
		SmartString &operator=(const SmartString & other){}
		
		string* str_;
};