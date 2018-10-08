#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <array>
#include <thread>
#include <stdlib.h>

const int num = 3;
pthread_t total_thread[num];
pthread_t pthread_self(void);
bool all_threads_created = false;
pthread_t main_thread = pthread_self();

int count = 0;
int current_num_of_thread = 0;
int threadid[num] = {0};
int setlock = 0;
int setlock_counter = 0;
int current_lock = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t method1_lock = PTHREAD_MUTEX_INITIALIZER;

const int ticket_total = 3;
bool ticket_array[ticket_total] = {false};

void door();
void create_threads();
void *start_func(void* ptr);
void create_threads();
void spin();
void ticket_lock();
void method1();
void method2();
void method3();

using namespace std;
using namespace std::chrono;


/*class Ticket_Lock{
public:
	Ticket_Lock()
		{lock_number = 0;}
	Ticket_Lock(int num)
		{lock_number = num;}
	int getnumber()
		{return lock_number;}
	void set_number(int num)
		{lock_number = num;}
	bool same_number(int num)
		{return(lock_number == num);} 

private:
	int lock_number;
};*/

//Ticket_Lock* thread_lock = new Ticket_Lock;
//thread_lock.set_number(main_thread);

int main(){
	//time_point<system_clock> start,end;
	//start = system_clock::now();

	ticket_array[0] = true;
	
	create_threads();

	while(!all_threads_created)
	{	}	
	setlock = threadid[0];
	
	//Ticket_Lock ticket;
	//ticket.set_number(thId);
	//cout << thId << "edd" << endl;
    for (int i = 0; i < num; i++){
        pthread_join(total_thread[i], NULL);
    } 
    //end = system_clock::now();
	//duration<double> elapsed_seconds = end - start;
	
	//cout << main_thread << endl;
}

void create_threads()
{
	for (int i = 0; i < num; i++){
        pthread_create(&(total_thread[i]), NULL, start_func, NULL);
    }
    all_threads_created = true;	
}

void *start_func(void* ptr)
{
	//pthread_t thId = pthread_self();
	//threadid[current_num_of_thread] = thId;
	//current_num_of_thread = 0;
	//start = system_clock::now();
	pthread_t thId = pthread_self();
	threadid[setlock_counter] = thId;
	setlock_counter++;

	for(int i; i<num;i++)
	{
		cout<<threadid[i]<<endl;
	}
	//pthread_t thId = pthread_self();
	//Ticket_Lock ticket;
	//ticket.set_number(thId);
	while(!all_threads_created)
	{}	
	time_point<system_clock> start,end;
	start = system_clock::now();
	//method1();
	//method2();
	//method3();
	end = system_clock::now();


	//duration<double> elapsed_seconds = end - start;
	//elapsed_seconds = elapsed_seconds * 1000000;
	//pthread_t thId = pthread_self();
	
	//cout << thId << "\t" << elapsed_seconds.count() <<endl;
	cout << thId<<endl;
	//method2();
	
}

void door()
{
	pthread_mutex_lock(&lock);
	//time_point<system_clock> start,end;
	//start = system_clock::now();
	//end = system_clock::now();

	//duration<double> elapsed_seconds = end - start;
	//elapsed_seconds = elapsed_seconds * 1000000;
	//cout << count << "\t" << elapsed_seconds.count() <<endl;
	count++;
	pthread_mutex_unlock(&lock);
}

void method1()
{
	pthread_mutex_lock(&method1_lock);
	time_point<system_clock> start,end;
	start = system_clock::now();
	door();
	end = system_clock::now();
	duration<double> elapsed_seconds = end - start;
	elapsed_seconds = elapsed_seconds * 1000000;

	pthread_t thId = pthread_self();
	
	cout << thId << "\t" << elapsed_seconds.count() << "method1" << endl;

	
	pthread_mutex_unlock(&method1_lock);
}
void method2()
{
	int total = 0;

	time_point<high_resolution_clock> start,end;
	start = system_clock::now();

	while(ticket_array[total] != true)
	{
		if(total < ticket_total)
			total++;
	}
	if(ticket_array[total] == true)
	{
		if(total <= ticket_total-1)
			ticket_array[total+1] = true;
	}
	
	end = system_clock::now();
	duration<double> elapsed_seconds = end - start;
	elapsed_seconds = elapsed_seconds * 1000000;

	pthread_t thId = pthread_self();
	
	cout << thId << "\t" << elapsed_seconds.count() << "method2" <<endl;
}
void method3()
{
	pthread_t thId = pthread_self();
	time_point<high_resolution_clock> start,end;
	start = system_clock::now();
	while(setlock != thId)
	{
		setlock = threadid[current_lock];
		
	}
	if(current_lock < num-2)
	{
		current_lock++;
		setlock = threadid[current_lock]; 
	}
	
	end = system_clock::now();
	duration<double> elapsed_seconds = end - start;
	elapsed_seconds = elapsed_seconds * 1000000;
	cout << thId << "\t" << elapsed_seconds.count() <<endl;
}
void ticket_lock()
{

}
void spin()
{
	
	

}