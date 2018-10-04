
#include <stdlib.h>
#include <string>
#include <pthread.h>

//#include <iostream>

#include <stdio.h>

// compile with gcc -pthread -o lab2 lab2.CPP
//  --tool=helgrind


void *print_message_function( void *ptr );

void *add_one(void *ptr);
void create_threads(int num);
void add_one_brute();

bool all_threads_created = false;
const int num_threads = 1;
bool pthread_lock = false;

const int method = 0;
int count = 0;

int door;

pthread_t arr_th[num_threads];

using namespace std;

int main(){
    create_threads(num_threads);
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
    printf("RELEASED '\n'");
    if (method == 0){
        add_one_brute();
    }
}

void add_one_brute(){
    while (pthread_lock){}
    pthread_lock = true;
    //count++;
    //printf("count = %d '\n'", count);
    pthread_lock = false;
}