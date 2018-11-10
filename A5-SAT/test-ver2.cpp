#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

struct Tree
{
	string sol;
	Tree* left;
	Tree* right;
};

struct Node
{
	string value;
	bool unknown;
	bool true_false;
	Node* next;
};

vector<vector<int>> vec;

string variable;
string clauses;
void input_reader();

int main(){
	cout << "Hello";
	input_reader();
    /*
	for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec.at(i).size(); j++){
            cout << i << ":" << vec.at(i).at(j) << endl;
        }
        
    }*/
	return 0;
}

void input_reader()
{
    cout << "input reader";
	ifstream inFile;
	inFile.open("file.txt");
	string str;
	if(!inFile)
	{
		cerr << "No input";
		exit(1);
	}
	else
	{
		inFile.ignore(1000,' ');
		inFile.ignore(1000,' ');

        int temp;

        int pos = 0;
        int pos_cl = 0;
        int var = 3;
        int clauses = 2;

        cout << "start reading";
        for (; pos_cl < clauses; pos_cl++){
            while (inFile >> temp){
                vec.at(pos_cl).push_back(temp);
                pos++;
                cout << "i = " << pos;
                if (pos >= var){
                    break;
                }
                   
            }
        }
        cout << "end reading";

//        istream_iterator<int> start(inFile), end;
//       vec(start, end);

		
	}

}




