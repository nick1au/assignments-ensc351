#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <ctype.h>   //for ispunct()
#include <map>
#include <iterator>  //for iterator
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

void input_reader(std::vector<string> &v);
void mapper(std::map<string, int> &map, std::vector<string> &v);
void reducer(std::map<string, int> &wordcounts);
void print_map(std::map<string, int> &wordcounts);


int main(){

	time_point<system_clock> start,end;
	start = system_clock::now();

	std::vector<string> v;
	std::vector<pair<string, int>> map_vector;
	pair<string, int> temp;
	map<string,int> wordcounts;
	std::map<string, int>::iterator jt;
	std::map<string, int>::iterator kt;
	std::pair<std::map<string, int>::iterator, bool> it;
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

	for(int i = 0; i < v.size(); i++)
	{
		str = v.at(i);
		it = wordcounts.insert(make_pair(str, 1));
		if(it.second == false)
			it.first->second++;

	}
	

	for(jt = wordcounts.begin(); jt != wordcounts.end(); jt++)
		map_vector.push_back(*jt);

	for(int i = 0; i < map_vector.size(); i++)
	{
		for(int j = i+1; j < map_vector.size(); j++)
		{
			if(map_vector.at(j).second < map_vector.at(i).second)
			{
				temp = map_vector.at(i);
				map_vector.at(i) = map_vector.at(j);
				map_vector.at(j) = temp;
			}
		}
	}

	//for(int i = 0; i < map_vector.size(); i++)
	//	cout << map_vector.at(i).first << "\t" << map_vector.at(i).second << endl;

	end = system_clock::now();
	duration<double> elapsed_seconds = end - start;
	
	cout << elapsed_seconds.count() <<endl;

	return 0;
}

