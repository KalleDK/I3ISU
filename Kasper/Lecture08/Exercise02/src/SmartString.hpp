 #include <iostream>
 #include <string>

class SmartString
{
	public:	
		SmartString(std::string* str) : str_(str), counter_(new unsigned int(1))
		{
			std::cout << "Counter_ at ctor: \t" << *counter_ << std::endl;
		}
		~SmartString()
		{
			std::cout << "Counter_ at dtor: \t" << *counter_ << std::endl;
			if(--(*counter_) <= 0){
				delete str_;
				delete counter_;
			}
		}
		std::string* get()
		{
			return str_;
		}
		std::string* operator->()
		{
			return str_;
		}
		std::string& operator*()
		{
			return *str_;
		}
		SmartString(const SmartString& other) 
		{
			str_ = other.str_;
			counter_ = other.counter_;
			++(*other.counter_);
			std::cout << "Counter_ at copyctor: \t" << *other.counter_ << std::endl;
		}
		
		SmartString& operator=(SmartString other)
		{
			other.swap(*this);
		}
	private:
		std::string* str_;
		unsigned int* counter_;
		
		void swap(SmartString& other)
		{
			std::swap(str_, other.str_);
		}
};