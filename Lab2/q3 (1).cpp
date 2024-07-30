#include <iostream>
#include<fcntl.h>
#include<unistd.h>
#include <cstdlib>
using namespace std;
int main(int argc,char *arg[]){
    int size= argc-1;
    int *arr=new int[size];
    int sum=0;
    
    for (int i=0; i<=size; i++){
      arr[i]=atoi(arg[i]);
      
     }
     for(int i=0;i<=size;i++){
       sum=sum+arr[i];
       }
       
    float average;
    average=sum/size;
    
    cout<<"The sum of integers is "<<sum<<endl;
    cout<<"The average of integer is "<<average<<endl;
    
 return 0;



}

