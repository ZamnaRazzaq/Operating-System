#include <iostream>
#include<fcntl.h>
#include<unistd.h>
#include <cstdlib>
using namespace std;
int main(int argc,char *arg[]){
    int size= argc-1;
    int *arr=new int[size];
    
    for (int i=0; i<=size; i++){
      arr[i]=atoi(arg[i]);
      
     }
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
            
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
