#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<iostream>
using namespace std;

int main(){

pid_t pid;
pid=fork();
  if (pid<0){
   cout<< "child process not created";
   }
  if (pid==0){
   cout<<"Child process created"<<endl;
   int status=execlp("/bin/ls", "ls", nullptr);
    if (status==-1){
      cout<<" command did not run successfully"<<endl;
      }
    }
    else {
      cout<<"In parent process"<<endl;
      cout<<"Parent process is waiting for child process to complete"<<endl;
      wait(NULL);
      cout<<"child process has completed";
   }
   return 0;
   

}
