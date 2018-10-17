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
//#include "Trace-lib.h"

#define total_threads 8

using namespace std;
using namespace std::chrono;

thread threadid[total_threads];
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
//void reduce_wrapper(std::vector<pair<string, int>> &v);

std::vector<pair<string, int>> collected_map;


int main() {
	//trace_start("log.txt");
	time_point<system_clock> start,end;
	start = system_clock::now();
	

	std::vector<string> v;
	std::vector<pair<string, int>> reduced_vect;
	
    input_reader(v);  
    
    for(int i = 0; i < total_threads; i++) //total number of threads.
    	threadid[i] = thread(mapper_wrapper, i, ref(v));
    for(int i = 0; i < total_threads; i++)
    	threadid[i].join();

    sort_vector(collected_map);

	//for (int i = 0; i < collected_map.size(); i++)
	//	cout << collected_map.at(i).first;

	//for(int i = 0; i < total_threads; i++) //total number of threads.
    //	threadid[i] = thread(reduce_wrapper, i, ref(v));	

//

    int j = 0;
	int i = 0;

	for(; i < collected_map.size();)
	{
		j = i + 1;
		if(j < collected_map.size())
		{
			while(j < collected_map.size() && (collected_map.at(i).first.compare(collected_map.at(j).first) == 0))
			{		
				j++;
			}
			reduced_vect.push_back(reducer(make_vect(collected_map, i, j)));
		}
		i = j;
		if(i == collected_map.size() - 1 && j == collected_map.size() - 1)
			reduced_vect.push_back(reducer(make_vect(collected_map, i, j+1)));
	}

//

	sort_by_value(reduced_vect);
	//print_vect(reduced_vect);

	end = system_clock::now();
	duration<double> elapsed_seconds = end - start;
	
	cout << elapsed_seconds.count() <<endl;
    
    return 0;
}
/*
void reduce_wrapper(int tid, std::vector<pair<string, int>> &input_v){
    int j = 0;
	int i = 0;

	for(; i < collected_map.size();)
	{
		j = i + 1;
		if(j < collected_map.size())
		{
			while(j < collected_map.size() && (collected_map.at(i).first.compare(collected_map.at(j).first) == 0))
			{		
				j++;
			}
			reduced_vect.push_back(reducer(make_vect(collected_map, i, j)));
		}
		i = j;
		if(i == collected_map.size() - 1 && j == collected_map.size() - 1)
			reduced_vect.push_back(reducer(make_vect(collected_map, i, j+1)));
	}
}
*/
void input_reader(std::vector<string> &v)
{
	ifstream inFile;
	inFile.open("sample.txt");
	string str;

	if(!inFile){
		cerr << "No";
		exit(1);
	}

	while(inFile>>str)
	{
		v.push_back(str);
	}	

}

pair<string, int> mapper(string str)
{
	
	return make_pair(str, 1);
	
}

void mapper_wrapper(int tid, vector<string> &input_vector)
{
	
	pair<string, int> map_entry;
	string word;
	for(int i = tid * (input_vector.size() / total_threads); i < (tid * (input_vector.size() / total_threads)) + (input_vector.size() / total_threads); i++)
	{
		word = input_vector[i];
		map_entry = mapper(word);
		thread_lock.lock();
		collected_map.push_back(map_entry);
		thread_lock.unlock();
	}
	
}

void print_vect(std::vector<pair<string, int>> &vect)
{
	for(int i = 0; i < vect.size(); i++)
	{
		cout << vect.at(i).first << "\t" << vect.at(i).second << endl;
	}
}
void print_vect(std::vector<string> &vect)
{
	for(int i = 0; i < vect.size(); i++)
	{
		cout << vect.at(i) << endl;
	}
}
pair<string, int> reducer(std::vector<pair<string, int>> vect)
{
	int count = 0;
	int i = 0;
	while(i < vect.size())
	{
		i++;
	}
	return make_pair(vect.at(0).first, i);
	
}
void sort_by_value(std::vector<pair<string, int>> &vect)
{
	pair<string, int> temp;
	for(int i = 0; i < vect.size(); i++)
	{
		for(int j = i+1; j < vect.size(); j++)
		{
			if(vect.at(j).second > vect.at(i).second)
			{
				temp = vect.at(i);
				vect.at(i) = vect.at(j);
				vect.at(j) = temp;
			}
		}
	}
}
void sort_vector(std::vector<pair<string, int>> &vect)
{
	pair<string, int> temp;
	for(int i = 0; i < vect.size(); i++)
	{
		for(int j = i+1; j < vect.size(); j++)
		{
			if(vect.at(j).first.compare(vect.at(i).first) < 0)
			{
				temp = vect.at(i);
				vect.at(i) = vect.at(j);
				vect.at(j) = temp;
			}
		}
	}
}
std::vector<pair<string, int>> make_vect(vector<pair<string, int>> &vect, int start, int end)
{
	vector<pair<string, int>> temp_vect;
	for(int i = start; i < end; i++)
	{
		temp_vect.push_back(vect.at(i));
	}
	return temp_vect;
}