  #include <unistd.h>
  #include <string.h>
  #include <sys/types.h>
  #include <sys/wait.h>
  #include <cmath>
  #include<iostream>
  using namespace std;

  int main()
  {
    pid_t pid;
    pid=fork();
    int p[2], c[2];
    pipe(p),pipe(c);
  if (pid<0){
   cout<< "child process not created";
   }
  if (pid==0){
      cout<<"Child process created"<<endl;
      close(c[0]);
      close(p[1]);
      int num;
      double Squareroot;
      read(p[0], &num, sizeof(num));
        Squareroot=sqrt(num);
      write(c[1],&Squareroot,sizeof(Squareroot));
      close(c[1]);
      close(p[0]);  
      }
    else {
      close(c[1]);
      close(p[0]);
      int num;
      cout<<"In parent process"<<endl;
      cout<<"Parent process is waiting for child process to complete"<<endl;
      cout<<"Enter number"<<endl;
      cin>>num;
      write(p[1],&num, sizeof(num));
      close(p[1]);
      double Squareroot;
      read(c[0],&Squareroot,sizeof(Squareroot));
      close(c[0]);
      cout<<"Original number"<<num<<endl;
      cout<<"Square root"<<Squareroot<<endl;
      cout<<"child process has completed";
   }
   return 0;
    }
