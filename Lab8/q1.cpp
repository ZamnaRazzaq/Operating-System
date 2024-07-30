#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
sem_t sema, semb, semc;
int count=0;
void* printa(void* arg) {
while(true){
    cout << "a";
    count=count+1;
    if(count==3){
    sem_post(&semc);
    sem_wait(&sema);
    count=0;
}
}
 return 0;
}

void* printb(void* arg) {
  while(true){
    sem_wait(&semb);
    cout << "b";
    sem_post(&sema);
  }
   return 0;
}

void* printc(void* arg) {
  while(true){
    sem_wait(&semc);
    cout << "c";
    sem_post(&semb);
  }
   return 0;
}

int main() {
  sem_init(&sema,0,0);
  sem_init(&semb,0,0);
  sem_init(&semc,0,0);

  pthread_t thread1, thread2, thread3;
 
  pthread_create(&thread1,NULL,printa,NULL);
  pthread_create(&thread2,NULL,printb,NULL);
  pthread_create(&thread3,NULL,printc,NULL);

  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);
  pthread_join(thread3,NULL);


  sem_destroy(&sema);
  sem_destroy(&semb);
  sem_destroy(&semc);

  return 0;
}
