#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

sem_t sem1,sem2;
int counter = 0;
int n;
void* incrementer(void* arg) {
    int id = *((int*)arg);
        sem_wait(&sem1);
        counter++;
        cout <<"Thread "<<counter<<" Counter: " << counter << endl;
        sem_post(&sem1);
        sem_post(&sem2);   
    pthread_exit(NULL);
}
void* print(void* arg){
  for (int i = 0; i < n; i++) { 
    sem_wait(&sem2);
  }
cout<<"All the threads have finish there execution"<<endl;
pthread_exit(NULL);
}

int main() {
    cout<<"Enter number of threads ";
    cin>>n;
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    pthread_t thread[n];
    pthread_t threadsp;
    
    for (int i=0; i<n;i++){
    pthread_create(&thread[i], NULL, incrementer, &i); }
    
    for (int i=0; i<n;i++){
    pthread_join(thread[i], NULL); }
    
    pthread_create(&threadsp, NULL, print,NULL); 
    pthread_join(threadsp,NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    
    return 0;
}
