#include <iostream>
#include <string>

using namespace std;

class SmartString {
	public:
		SmartString(string* str):str_(str), counter_(new unsigned int(1)){}
		
		~SmartString(){
			if (--(*counter_) <= 0) {
				delete str_;
				delete counter_;
			}
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
		
		SmartString(const SmartString & other):str_(other.str_),counter_(other.counter_){
			(*counter_)++;
		}
		
		SmartString &operator=(SmartString other){
			other.swap(this);
		}
		
		//Til at kunne udskrive counter_ 
		unsigned int getCount() const{
			return *counter_;
		}
	private:
		string* str_;
		unsigned int* counter_;
		
		void swap(SmartString* other)
		{
			std::swap(str_, other->str_);
			std::swap(counter_, other->counter_);
		}
};