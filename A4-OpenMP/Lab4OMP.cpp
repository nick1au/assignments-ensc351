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
#include <iterator>
#include <omp.h>

#define total_threads 4 // Global for num of threads - not used for OMP

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

std::vector<pair<string, int>> collected_map;

// A bool func to compare two pairs for sort by string
bool waytosort(pair<string, int> pair1, pair<string, int> pair2)
{
	return (pair1.first.compare(pair2.first) < 0);
}

// A bool func to sort by integer for sort by the value
bool waytosortbyint(pair<string, int> pair1, pair<string, int> pair2)
{
	return (pair1.second > pair2.second);
}

int main() {
	time_point<system_clock> start,end;
	start = system_clock::now();

	std::vector<string> v;
	std::vector<pair<string, int>> reduced_vect;
	
    input_reader(v);


	#pragma omp parallel
		for (int i = 0; i < v.size(); i++){
			#pragma omp single
			collected_map.push_back(mapper(v.at(i)));
		}
	//cout << "PRINT COL" << endl;
  	//print_vect(collected_map);
    
    sort(collected_map.begin(), collected_map.end(), waytosort);
    
    unsigned int j = 0;
	unsigned int i = 0;
	//i = 0;

	//for(unsigned int i = omp_get_thread_num() * (v.size() / omp_get_num_threads()); 
  	//		i < (omp_get_thread_num() * (v.size() / omp_get_num_threads())) + (v.size() / omp_get_num_threads()); i++)


	//#pragma omp parallel //shared(i,j) //reduction(+:j)


	if (collected_map.size() == 1){
		reduced_vect.push_back(reducer(make_vect(collected_map, 0, 1)));
	}

	for (i = 0; i < collected_map.size();i++)
	{
		#pragma omp single
		{
		j = i + 1;
		if(j < collected_map.size())
		{
		//	for (; j < collected_map.size() && (collected_map.at(i).first.compare(collected_map.at(j).first) == 0); j++)
			
			while(j < collected_map.size() && (collected_map.at(i).first.compare(collected_map.at(j).first) == 0))
			{		
				j++;
			}
	
					reduced_vect.push_back(reducer(make_vect(collected_map, i, j)));
	
		}
		i = j;
	//		#pragma omp single
		
		if(i == collected_map.size() - 1 && j == collected_map.size() - 1){
				
			reduced_vect.push_back(reducer(make_vect(collected_map, i, j+1)));
		}
		
			i--;
		}
	}
	
	sort(reduced_vect.begin(),reduced_vect.end(),waytosortbyint);
    print_vect(reduced_vect);
	end = system_clock::now();
	duration<double> elapsed_seconds = end - start;
	
	cout << elapsed_seconds.count() <<endl;
    
    return 0;
}
// Read the text file
void input_reader(std::vector<string> &v)
{
	ifstream inFile;
	inFile.open("sample.txt");
	string str;

	if(!inFile){ // Error checking
		cerr << "No file present";
		exit(1);
	}

	while(inFile>>str)
	{
		v.push_back(str);
	}	

}

//Makes the key-value pair
pair<string, int> mapper(string str)
{
	
	return make_pair(str, 1);
	
}

// A wrapper for mapping threads - not used for OMP
void mapper_wrapper(int tid, vector<string> &input_vector)
{
	thread_lock.lock();
	pair<string, int> map_entry;
	string word;
	for(unsigned int i = tid * (input_vector.size() / total_threads); i < (tid * (input_vector.size() / total_threads)) + (input_vector.size() / total_threads); i++)
	{
		word = input_vector[i];
		map_entry = mapper(word);
		collected_map.push_back(map_entry);
	}
	thread_lock.unlock();
}

// Print a key-value pair vector
void print_vect(std::vector<pair<string, int>> &vect)
{
	for(unsigned int i = 0; i < vect.size(); i++)
	{
		cout << vect.at(i).first << "\t" << vect.at(i).second << endl;
	}
}

// Print a string based vector
void print_vect(std::vector<string> &vect)
{
	for(unsigned int i = 0; i < vect.size(); i++)
	{
		cout << vect.at(i) << endl;
	}
}

// Reducer function
pair<string, int> reducer(std::vector<pair<string, int>> vect)
{
	std::vector<pair<string, int>>::iterator it;
	it = vect.begin();
	return make_pair(it->first, vect.size());
	
}

// Sort the list by value
void sort_by_value(std::vector<pair<string, int>> &vect)
{
	pair<string, int> temp;
	for(unsigned int i = 0; i < vect.size(); i++)
	{
		for(unsigned int j = i+1; j < vect.size(); j++)
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

// Make the vector
std::vector<pair<string, int>> make_vect(vector<pair<string, int>> &vect, int start, int end)
{
	vector<pair<string, int>> temp_vect;
	for(int i = start; i < end; i++)
	{
		temp_vect.push_back(vect.at(i));
	}
	return temp_vect;
}
