#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<iostream>
using namespace std;

int main(){
pid_t child1,child2,child3,child4;
int status;
 
 {
child1=fork();
  if (child1<0){
    cout<<"Child 1 is not created"<<endl;
  }
  if (child1==0){
  cout<<"Child 1 has been created"<<endl;
  status=execlp("/bin/mkdir", "mkdir", "my_directory", nullptr);
  if (status==-1){
      cout<<" command did not run successfully"<<endl;
      }
   
    }
   }
   {
child2=fork();
  if (child2<0){
    cout<<"Child 2 is not created"<<endl;
  }
  if (child2==0){
  cout<<"Child 2 has been created"<<endl;
  status=execlp("/bin/cp", "cp", "Input File.txt", "my_directory/", nullptr);
  if (status==-1){
      cout<<" command did not run successfully"<<endl;
      }
    }
    }
{
child3=fork();
  if (child3<0){
    cout<<"Child 3 is not created"<<endl;
  }
  if (child3==0){
  cout<<"Child 3 has been created"<<endl;
  status=execlp("/bin/rmdir", "rmdir", "/home/zamna/Documents/lab2/qwe", nullptr);
  if (status==-1){
      cout<<" command did not run successfully"<<endl;
      }
    }
    }
{
child4=fork();
  if (child4<0){
    cout<<"Child 4 is not created"<<endl;
  }
  if (child4==0){
  cout<<"Child 4 has been created"<<endl;
  status=execlp("/bin/rm", "rm", "Output file.txt", nullptr);;
  if (status==-1){
      cout<<" command did not run successfully"<<endl;
      }
    }
    }
   cout<<"Parent process is waiting for child process to complete"<<endl;
   wait(NULL);
   cout<<"All the child processes have completed";
   
   return 0;
}
    
    
    
    
    
