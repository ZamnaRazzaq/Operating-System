#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;
int main(){

pid_t pid;
pid=fork();

int fd1[2];
if ((pipe(fd1[2])==-1){
  cout<<"pipe failed"<<endl;
  }

if (pid<0){
  cout<<"Fork failed"<<endl;
  }
if (pid==0){
   cout<<"In child process"<<endl;
   close(fd1[0]);
   dup2(fd1[1],STDOUT_FILENO);
   execlp("man","man","ls",nullptr);
   }
elseif (pid>0){
   close(fd1[1];
   int openfile=open("myfile.txt",O_WRONLY);
   dup2(fd1[0],STDIN_FILENO);
   dup2(openfile,STDOUT_FILENO);
   execlp("grep","grep","ls",nullptr);
   }
return 0;
}

