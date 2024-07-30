#include <stdlib.h>
#include<iostream>
#include <pthread.h>
#include <stdio.h>
using namespace std;
void *fibonnaciGenerator(void* n){
int t1 = 0, t2 = 1, nextTerm = 0;
cout << "Fibonacci Series: " << t1 << ", " << t2 << ", ";

    nextTerm = t1 + t2;
    int x=atoi((const char*)n);
    while(nextTerm <= x) {
        cout << nextTerm << ", ";
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }
    pthread_exit(0);

}
int main(int argc,char *argv[]){
int size=argc-1;
for(int i=0;i<size;i++){
pthread_t threadID;
pthread_attr_t attributes;
pthread_attr_init(&attributes);
pthread_create(&threadID, &attributes,fibonnaciGenerator,(void*)argv[i+1]);
pthread_join(threadID, NULL);
}
return 0;

}

