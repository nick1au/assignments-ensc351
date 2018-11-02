#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct SAT
{
	vector<string> clause;
	bool verify;
};

struct Solution
{
	string value;
	bool true_false;
};

vector<SAT> Big_Expression;
vector<Solution> Answer;
int total_variables;
int total_clauses;


void read_into_vector(vector<string>);
void delete_temp_vector(vector<string>&);
void input_reader();
void display();
void initializing_solution_vector();
void initiate_compare_protocol(Solution&); 
void purpose_solution();
bool checking_solution();

int main(){
	input_reader();
	initializing_solution_vector();
	if(checking_solution())
		cout << "true";
	return 0;
}

void input_reader()
{
	ifstream inFile;
	inFile.open("file.txt");
	string str;
	vector<string> temp;
	if(!inFile)
	{
		cerr << "Error";
		exit(1);
	}
	else
	{
		inFile.ignore(1000,' ');
		inFile.ignore(1000,' ');
		inFile >> total_variables;
		inFile >> total_clauses;
		while(inFile >> str)
		{
			if(str != "0")
				temp.push_back(str);
			else if(str == "0")
			{
				read_into_vector(temp);
				delete_temp_vector(temp);
			}
		}
	}
}

void read_into_vector(vector<string> vect)
{
	SAT temp;
	temp.clause = vect;
	temp.verify = false;
	Big_Expression.push_back(temp);
}
void display()
{
	SAT temp;
	for(unsigned int i = 0; i < Big_Expression.size(); i++)
	{
		temp = Big_Expression.at(i);
		for(unsigned int j = 0; j < temp.clause.size(); j++)
			cout << temp.clause.at(j) << endl;
	}
}
void delete_temp_vector(vector<string>& vect)
{
	while(vect.size() != 0)
	{
		vect.pop_back();
	}
}

void initializing_solution_vector()
{
	for (unsigned int i = 1; i <= total_variables; ++i)
	{
		Solution sol = {to_string(i), false};
		Answer.push_back(sol);
	}
}
void purpose_solution()
{
	for (unsigned int i = 0; i < Answer.size(); ++i)
	{
		initiate_compare_protocol(Answer.at(i));
	}
}
bool checking_solution()
{
	SAT temp;
	for (unsigned int i = 0; i < Big_Expression.size(); ++i)
	{
		temp = Big_Expression.at(i);
		for (unsigned int j = 0; i < temp.clause.size(); ++j)
		{
			if(temp.verify == false)
				return true;
		}
	}
	return false;
}
void initiate_compare_protocol(Solution& sol)
{
	SAT temp;
	for (unsigned int i = 0; i < Big_Expression.size(); ++i)
	{
		temp = Big_Expression.at(i);
		for (unsigned int j = 0; i < temp.clause.size(); ++j)
		{
			if(sol.value == temp.clause.at(i))
			{
				sol.true_false = true;
				if(temp.verify == false)
					temp.verify = true;
			}
		}
	}
}

