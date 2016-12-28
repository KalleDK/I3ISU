#include <iostream>
#include <string>

using namespace std;

template <class T>
class SmartPointer {
	public:
		SmartPointer(T* t):t_(t), counter_(new unsigned int(1)){}
		
		~SmartPointer(){
			if (--(*counter_) <= 0) {
				delete t_;
				delete counter_;
			}
		}
		
		T* get(){ 
			return t_;
		}
		
		T *operator->(){
			return t_;
		}
		
		T &operator*(){
			return *t_;
		}
		
		SmartPointer(const SmartPointer & other):t_(other.t_),counter_(other.counter_){
			(*counter_)++;
		}
		
		SmartPointer &operator=(SmartPointer other){
			other.swap(this);
		}
		
		//Til at kunne udskrive counter_ 
		unsigned int getCount() const{
			return *counter_;
		}
	private:
		T* t_;
		unsigned int* counter_;
		
		void swap(SmartPointer* other)
		{
			std::swap(t_, other->t_);
			std::swap(counter_, other->counter_);
		}
};