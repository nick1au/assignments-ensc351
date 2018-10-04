
#include <stdlib.h>
#include <string>
#include <pthread.h>

//#include <iostream>

#include <stdio.h>
//#include <unistd.h>
//#include <mutex>
#include <thread>

// compile with gcc -pthread -o lab2 lab2.CPP
//  --tool=helgrind


void *print_message_function( void *ptr );

void *add_one(void *ptr);
void create_threads(int num);
void add_one_brute();

bool all_threads_created = false;
const int num_threads = 15;
//bool pthread_lock = false;
pthread_mutex_t pthread_lock = PTHREAD_MUTEX_INITIALIZER;

const int method = 0; // 0 = brute-force, 1 = spin, 2 = ticket queue
int count = 0;

int door;

pthread_t arr_th[num_threads];

using namespace std;

int main(){
    create_threads(num_threads);
    for (int i = 0; i < num_threads; i++){
        pthread_join(arr_th[i], NULL);
    } // similar to join()
    printf("DONE processing '\n'");
    printf("Final count = %d '\n'", count);
    return 0;
}

void create_threads(int num){
    const char *msg = "test";
    for (int i = 0; i < num; i++){
        pthread_create(&(arr_th[i]), NULL, add_one, NULL);
        printf("Created thread %d '\n' ", i);
    }
    all_threads_created = true;
}

void *add_one(void *ptr){
    while (!all_threads_created){}
    //printf("RELEASED '\n'");
    if (method == 0){
        //while (pthread_lock){}
        pthread_mutex_lock(&pthread_lock);
        add_one_brute();
        pthread_mutex_unlock(&pthread_lock);
    }
    else if (method == 1){
        //while (pthread_lock){}
        //...
    }
    else if (method == 2){

    }
}

void add_one_brute(){  
    count++;
    printf("count = %d '\n'", count);
}

