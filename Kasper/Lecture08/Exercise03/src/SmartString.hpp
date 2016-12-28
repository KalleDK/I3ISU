 #include <iostream>
 #include <string>

template <class T>
class SmartString
{
	public:	
		SmartString(T* str) : str_(str), counter_(new unsigned int(1))
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
		T* get()
		{
			return str_;
		}
		T* operator->()
		{
			return str_;
		}
		T& operator*()
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
			return *this;
		}
	private:
		T* str_;
		unsigned int* counter_;
		
		void swap(SmartString& other)
		{
			std::swap(str_, other.str_);
			std::swap(counter_, other.counter_);
		}
};