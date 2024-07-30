#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
using namespace std;

sem_t semp, semc;
int buffer[100] = {0};
int count = 0;
int sum = 0;

void* producer(void* arg) {
    while (count < 100) {
        int n = rand() % 6;
        sem_wait(&semp);
        buffer[count] = n;
        char message[100];
        sprintf(message, "The number is : %d\n", n);
        puts(message);
        sem_post(&semc);
    }
    return 0;
}

void* consumer(void* arg) {
    while (count < 100) {
        sem_wait(&semc);
        sum = sum + buffer[count];
        char message[100];
        sprintf(message, "The sum is : %d\n", sum);
        puts(message);
        count++;
        sem_post(&semp);
    }
    return 0;
}

int main() {
    sem_init(&semp, 0, 1);
    sem_init(&semc, 0, 0);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, producer, NULL);
    pthread_create(&thread2, NULL, consumer, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&semp);
    sem_destroy(&semc);

    return 0;
}
