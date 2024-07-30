#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<iostream>
using namespace std;

int main(){

 pid_t pid[4],terminatepid;

  for (int i=0; i<4;i++){
    pid[i]=fork();
    
   if (pid[i]<0){
     cout<<"Fork Failed";
   }
   if (pid[i]==0){
   cout<<"Child processes have been created "<<endl;
 
   }
   } 
   cout<<"Parent process is waiting for child process to complete"<<endl;
    int status;
   for (int i = 0; i < 4; i++) {
        terminatepid = wait(&status);

        if (WIFEXITED(status)) {
           cout << "Child processes have been terminated"<<endl;
        }
    }
   cout<<"All the child processes have completed";
   return 0;
}

