#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <ctype.h>   //for ispunct()
#include <map>
#include <iterator>  //for iterator
#include <vector>

using namespace std;

void input_reader(std::vector<string> &v);
void mapper(std::map<string, int> &map, std::vector<string> &v);
void reducer(std::map<string, int> &wordcounts);
void print_map(std::map<string, int> &wordcounts);


int main(){

	std::vector<string> v;
	map<string,int> wordcounts;
	input_reader(v);
	mapper(wordcounts, v);
	reducer(wordcounts);
	print_map(wordcounts);
	return 0;
}

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
		//v.add(str);
		
	}
	for(int i = 0; i < v.size(); i++)
		cout << v.at(i)<< endl;
	
}
void mapper(std::map<string, int> &wordcounts, std::vector<string> &v)
{
	map<string,int>::iterator it;
	for(int i = 0; i < v.size(); i++)
	{
		wordcounts.insert(make_pair(v.at(i), 1));
	}
	for(it = wordcounts.begin(); it != wordcounts.end(); it++)
	{
		cout<<it->first << "\t" << it->second <<endl;

	
	}
}
void reducer(std::map<string, int> &wordcounts)
{
	string str_to_compare;
	int count = 0;
	map<string, int>::iterator it;
	map<string, int>::iterator jt;
	
	for(it = wordcounts.begin(); it != wordcounts.end(); it++)
	{
		str_to_compare = it->first;
		for(jt = it++; jt != wordcounts.end(); jt++)
		{
			if(str_to_compare.compare(jt->first) < 0)
			{
				swap(jt,it);
			}

		}
		count++;
	}
}

void print_map(std::map<string, int> &wordcounts)
{
	std::map<string, int>::iterator it;
	for(it = wordcounts.begin(); it != wordcounts.end(); it++)
		cout << it->first << "\t" << it->second <<endl;
}

