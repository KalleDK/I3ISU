#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "Vector.hpp"

using namespace std;

#define NUM_THREADS     20

Vector v1;
int count=0;

void*writer(void *n){
  int this_n = 0;
  this_n = (int) n;
  
  while(count < 50){
   if( v1.setAndTest(this_n) == false){
     count++;
     cout << "Number of mistakes: " << count << endl;
   }
     usleep(500);
 }
}

int main(){
  pthread_t threads[NUM_THREADS];
  
  for(int i=0; i<NUM_THREADS; i++){
    cout << "MAIN : creating thread, " << i << endl;
    pthread_create(&threads[i],NULL,writer,(void*)i);
  }
  
  for(int j=0; j<NUM_THREADS; j++){
    pthread_join(threads[j], NULL);
  }
  
  cout << "Main : Exiting" << endl;
}

