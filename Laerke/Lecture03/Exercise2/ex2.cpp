#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
unsigned int share = 0;

using namespace std;

void*reader(void *s){
  for(int i = 0; i <=10; i++)
  {
    cout << "share is: "<< share << endl;
    sleep(1);
  }
}

void*incrementer(void *s){
 
  for(int i = 0; i <=10; i++)
  {
    share ++;
    sleep(1);
  }
}


int main(){
  pthread_t inc;
  pthread_t read;
  
  pthread_create(&inc,NULL,incrementer,NULL);
  pthread_create(&read,NULL,reader,NULL);
  
  pthread_join(inc, NULL);
  pthread_join(read, NULL); 
}