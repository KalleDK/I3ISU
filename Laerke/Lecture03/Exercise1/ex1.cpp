#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void*print_ID(void *ID){
  int count=0;
  int this_ID;
  this_ID = (int) ID;
  
  for(count = 0; count<=10 ; count ++)
  {
  cout << "Hello #" << count << " from thread " << this_ID << endl;
  sleep(1);
  }
}

int main(){
  pthread_t t1;
  pthread_t t2;
  cout << "Main : Creating threads" << endl;
  cout << "Main : Waiting for threads to finish" << endl;
  
  pthread_create(&t1,NULL,print_ID,(void*)0);
  pthread_create(&t2,NULL,print_ID,(void*)1);
  
  pthread_join(t1, NULL);
  pthread_join(t2, NULL); 
  
  cout << "Main : Exiting" << endl;
}

