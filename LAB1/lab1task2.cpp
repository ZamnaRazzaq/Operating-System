#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(){

   int num;
   cout<<"Enter a number";
   cin>>num;

   pid_t pid;
   pid=fork();
    if (pid<0){
       cout<<"child process not created";
    }


       if (pid == 0) {

          if (num % 2==0){
              cout<<" This is an even number";
          } else {
              cout<<" This is an odd number";
          }
       } else {
          cout<< num;
       }
  return 0;
}       


     
 
   
