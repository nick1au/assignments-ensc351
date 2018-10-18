#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include "Trace-lib.h"

#define total_threads 4

using namespace std;
using namespace std::chrono;

thread threadid[x];
mutex thread_lock;

void input_reader(std::vector<string> &v);
void mapper_wrapper(int tid, std::vector<string> &v);
pair<string, int> mapper(string input);
void print_vect(std::vector<pair<string, int>> &vect);
void print_vect(std::vector<string> &vect);
pair<string, int> reducer(std::vector<pair<string, int>> vect);
void sort_by_value(std::vector<pair<string, int>> &vect);
std::vector<pair<string, int>> make_vect(vector<pair<string, int>> &vect, int, int);
void sort_vector(std::vector<pair<string,int>> &vect);

std::vector<pair<int[2], int>> collected_map;

bool waytosort(pair<string, int> pair1, pair<string, int> pair2)
{
	return (pair1.first.compare(pair2.first) < 0);
}

bool waytosortbyint(pair<string, int> pair1, pair<string, int> pair2)
{
	return (pair1.second > pair2.second);
}
const int x = 5;
const int y = 5;

int matrix2[x][y] = {
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6}
};

int matrix2[x][y] = {
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6}
};

int result[1][y];



int main(){
    int i = 0;
    while (i < x){
        for (i; i < total_threads + i; i++){
            threadid[i] = thread(handler, i);
        }
    }
    
    return 0;
}

void handler(int i){
    vector<pair<int[2], int>> res;
    map
}


input(){

}


void mapper_wrapper(int tid, vector<string> &input_vector)
{	
	trace_event_start((char*) "Map", (char*) "prog", (char*) "arg", tid);
	thread_lock.lock();
	pair<string, int> map_entry;
	string word;
	for(int i = tid * (input_vector.size() / total_threads); i < (tid * (input_vector.size() / total_threads)) + (input_vector.size() / total_threads); i++)
	{
		word = input_vector[i];
		map_entry = mapper(word);
		collected_map.push_back(map_entry);
	}
	thread_lock.unlock();
	trace_event_end((char*) "arg", tid);
}


vector<pair<int[2],int>> map(int ix, int iy){
    return make_pair(str, 1);
}