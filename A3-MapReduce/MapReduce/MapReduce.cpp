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
pair<string, int> mapper(string);
pair<string, int> reducer(vector<pair<string, int>> vect);
void sort_vector(std::vector<pair<string,int>> &vect);
void print_vect(std::vector<pair<string, int>> &vect);
void print_vect(std::vector<string> &vect);
std::vector<pair<string, int>> make_vect(vector<pair<string, int>> &vect, int, int);

int main(){

	std::vector<string> v;
	std::vector<pair<string, int>> map_vector;
	std::vector<pair<string, int>> reduced_vect;
	std::vector<pair<string, int>> temporary_vector;
	

	input_reader(v);
	
	
	//print_vect(v);
	//sort_vector(map_vector);

	for(int i = 0; i < v.size(); i++)
	{
		map_vector.push_back(mapper(v.at(i)));
	}
	print_vect(map_vector);
	
	sort_vector(map_vector);
	
	int j = 0;
	int i = 0;
	for(; i < map_vector.size();)
	{
		j = i + 1;
		if(j < map_vector.size())
		{
			while(j < map_vector.size() && (map_vector.at(i).first.compare(map_vector.at(j).first) == 0))
			{		
				j++;
			}
			reduced_vect.push_back(reducer(make_vect(map_vector, i, j)));
		}
		i = j;
		if(i == map_vector.size() - 1 && j == map_vector.size() - 1)
			reduced_vect.push_back(reducer(make_vect(map_vector, i, j+1)));
		//cout << "i = " << i << "\t j = " << j << endl;

	}
	
	print_vect(reduced_vect);
	
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
	}	

}

pair<string, int> mapper(string str)
{
	return make_pair(str, 1);
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
			
			//temporary_vector = make_vect(map_vector,i,j);
			//reduced_vect.push_back(reducer(temporary_vector));
			
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

void print_vect(std::vector<pair<string, int>> &vect)
{
	for(int i = 0; i < vect.size(); i++)
	{
		cout << vect.at(i).first << "\t" << vect.at(i).second << endl;
	}
	//for(it = wordcounts.begin(); it != wordcounts.end(); it++)
		//cout << it->first << "\t" << it->second <<endl;
}
void print_vect(std::vector<string> &vect)
{
	for(int i = 0; i < vect.size(); i++)
	{
		cout << vect.at(i) << endl;
	}
	//for(it = wordcounts.begin(); it != wordcounts.end(); it++)
		//cout << it->first << "\t" << it->second <<endl;
}






/*
for(int i = 0; i < map_vector.size(); i++)
	{
		if(j < map_vector.size())
			j = i + 1;
		while(map_vector.at(i).first.compare(map_vector.at(j).first) == 0)
		{
			if(j < map_vector.size())
				j++;
		}
		//temporary_vector = make_vect(map_vector,i,j);
		//reduced_vect.push_back(reducer(temporary_vector));
		i = j;
	}
*/
























/*
void input_reader(std::vector<string> &v);
void mapper(std::map<string, int> &map, std::vector<string> &v);
void reducer(std::map<string, int> &wordcounts);
void print_map(std::map<string, int> &wordcounts);


int main(){

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

	for(int i = 0; i < map_vector.size(); i++)
		cout << map_vector.at(i).first << "\t" << map_vector.at(i).second << endl;
		
	return 0;
}

*/