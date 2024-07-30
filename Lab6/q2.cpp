#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
int size=5;
void *min(void *arr) {
    int *array = (int *)arr;
    int min = array[0];

    for (int i = 0; i < size; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    cout << "Minimum element: " << min<< endl;
    pthread_exit(NULL);
}

void *max(void *arr) {
    int *array = (int *)arr;
    int max = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    cout << "Maximum element: " << max << endl;
    pthread_exit(NULL);
}

void *average(void *arr) {
    int *array = (int *)arr;
    int sum = 0;
    int average=0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    average = sum / size;
    cout << "Average: " << average << endl;
    pthread_exit(NULL);
}




int main(int argc, char *argv[])
{
int *arr=new int[size];
for (int i=0; i<size;i++){
  arr[i-1]=atoi(argv[i]);}

pthread_t thread1,thread2,thread3;
pthread_create(&thread1,NULL,average,(void*)arr);
pthread_create(&thread2,NULL,min,(void*)arr);
pthread_create(&thread3,NULL,max,(void*)arr);
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);
pthread_join(thread3, NULL);


}
