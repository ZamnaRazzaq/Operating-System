#include <iostream>
#include<cstring>
#include<fcntl.h>
#include<unistd.h>
#include <cstdlib>
#include<stdio.h>
#include<sys/types.h>
#include <sys/wait.h>
using namespace std;
int main(int argc,char *arg[]){
    int size= argc-1;
    int *arr=new int[size];
    float average=0;
    int max=0;
    int sum = 0;
    
    char* token=strtok(arg[1],"$");

     for (int i=0; i<=size; i++){
      arr[i]=atoi(token);
      
     }
     pid_t child1,child2,child3;
       child1=fork();
       if (child1==0){
          for(int i=0;i<=size;i++){
             sum=sum+arr[i];
          }
         cout<<"The sum of the array by child 1 is: "<<sum<<endl;
       }
       
      child2=fork();
       if (child2==0){
         average=sum/size;
         cout<<"The average of the array by child 2 is: "<<average<<endl;
       }
      child3=fork();
       if (child3==0){
         max = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        cout<<"The maximum of the array by child 2 is: "<<max<<endl;
       }
       
    return 0;
    
}


