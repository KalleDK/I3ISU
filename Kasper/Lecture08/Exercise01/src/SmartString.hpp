#include <string>

class SmartString
{
	public:	
		SmartString(std::string* str)
		{
			str_ = str;
		}
		~SmartString()
		{
			delete str_;
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
	private:
		std::string* str_;
		
		SmartString(const SmartString& other)
		{
			str_ = new std::string(*other.str_);
		}
		SmartString& operator=(const SmartString& other)
		{
			if(other.str_ != str_)
			{
				SmartString copy(other);
				
				delete str_;
				
				str_ = other.str_;
			}
			return *this;
		}
};