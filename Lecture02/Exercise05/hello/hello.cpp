// 'Hello World!' program 
#include <iostream>
using namespace std;
 
int main()
{
  #ifdef DEBUG
  cout << "Debug Enabled" << endl;
  #endif
  cout << "Hello World!" << endl;
  return 0;
}
