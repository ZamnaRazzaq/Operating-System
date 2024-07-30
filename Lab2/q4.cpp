#include <iostream> 
#include<stdio.h>
#include<sys/types.h>
using namespace std;
int main(){
      int *num=new int[15];
      num[0]=0;
      num[1]=1;
      
      pid_t pid;
      pid=fork();
   if (pid<0){
        cout<<"Child process is not created"<<endl;
   }
     if (pid==0){
        cout<<"Child Process: "<<endl;
      for (int i=0;i<13;i++){
          num[i+2]=num[i]+num[i+1];
      }
      for(int i=0; i<15;i++){
           cout<<num[i]<<" ";
      }
     }
     else{
       cout<<"Parent process: "<<endl;
       cout<<"Fibonacci series is as follow ";
       
         for(int i=0; i<15; i++){
           cout<<num[i]<<" ";
         }
     }
     return 0;
}


