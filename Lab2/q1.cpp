#include <iostream>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int main(int argc, char *arg[]){

    int fileread=open(arg[2],O_RDONLY);
    char charr;
       if (fileread==-1){
         cout<<"Unable to open file"<<endl;
       } 
         
         while(read(fileread,&charr,1)>0){
          cout<<charr;
         }
      
       
close(fileread);
return 0;
}
