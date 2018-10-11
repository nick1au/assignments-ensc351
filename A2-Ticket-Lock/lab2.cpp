// Lab2 - Thread Locks
// Nicholas Lau - 301290893 - NLA52@sfu.ca
// Wing Aung - ## - RAUNG@sfu.ca

#include <stdlib.h>
#include <string>

#include <chrono>
#include <ctime>

//#include <pthread.h>
#include <thread>

#include <iostream>

#include <stdio.h>
//#include <unistd.h>
#include <mutex>
#include <iomanip>

#include <atomic>

// compile with g++ -pthread -o lab2 lab2.CPP
//  --tool=helgrind


void *print_message_function( void *ptr );

//void *start_func(void *ptr);
void start_func(int ix);
void create_threads(int num);
void add_one();

bool all_threads_created = false;
const int num_threads = 100;
//bool pthread_lock = false;

// pthread_imp
//pthread_mutex_t pthread_lock = PTHREAD_MUTEX_INITIALIZER;
//pthread_t arr_th[num_threads];

std::thread arr_th[num_threads];
std::mutex thread_lock;

const int method = 2; // 1 = brute-force, 2 = spin, 3 = ticket queue
int count = 0;

//std::atomic_flag flag[num_threads] = {ATOMIC_FLAG_INIT};
bool flag[num_threads] = {true}; // false = locked, true = available

using namespace std;
using namespace std::chrono;

int main(){
    cout << "METHOD = " << method << endl;
    create_threads(num_threads);
    for (int i = 0; i < num_threads; i++){
        //pthread_join(arr_th[i], NULL); // pthread_imp
        arr_th[i].join();
        if (i == 0){
            //flag[i].clear(std::memory_order_acquire);
            flag[0] = true;
        }
        else{
            //flag[i].test_and_set(std::memory_order_acquire);
        }
    } // similar to join()
    printf("DONE processing '\n'");
    printf("Final count = %d '\n'", count);
    return 0;
}

void create_threads(int num){
    const char *msg = "test";
    for (int i = 0; i < num; i++){
        //pthread_create(&(arr_th[i]), NULL, start_func, &i); // pthread_imp
        //std::thread th(start_func, i);
        arr_th[i] = std::thread(start_func, i);
        //printf("Created thread %d '\n' ", i);
    }
    all_threads_created = true;
}
//void *start_func(void* ptr){ // pthread_imp
void start_func(int ix){
    while (!all_threads_created){}
    time_point<system_clock> start,end;
    //int ix = *(int*) ptr; // pthread_imp
    //cout << "IX THREAD " << ix << endl;
    start = system_clock::now();
    //printf("RELEASED '\n'");
    if (method == 1){ // brute-force
        
        //pthread_mutex_lock(&pthread_lock); // pthread_imp
        thread_lock.lock();
        add_one();
        //pthread_mutex_unlock(&pthread_lock); // pthread_imp
        thread_lock.unlock();
    }
    else if (method == 2){ // spin-lock
        //...
        while(flag[ix] == false){}//flag[ix].test_and_set(std::memory_order_acquire)){}
        //cout << "IX THREAD " << ix << endl;
        // printf("IX_THREAD %d '\n' ", ix);
        //flag[ix].clear(std::memory_order_acquire);
        if (ix < num_threads){
            //flag[ix+1].clear(std::memory_order_acquire);
            flag[ix + 1] = true;
        }
    }
    else if (method == 3){ //ticket-lock
        
    }

    end = system_clock::now();
	duration<double> elapsed_seconds = end - start;
    cout << std::fixed << std::setprecision(15) << elapsed_seconds.count() <<endl;
	//cout << std::setprecision(15)
    //cout << elapsed_seconds.count() <<endl;
}

void add_one(){  
    count++;
    //printf("count = %d '\n'", count);
}

