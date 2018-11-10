#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include "BinaryTree.h"
using namespace std;

void input_reader();
void read_into_vector(vector<int> vect);
void delete_temp_vector(vector<int>& vect);
void flush_compResult_vector();
void compare_result(vector<int> solution);
void print_end_status();

struct SAT {
	std::vector<int> clause;
	int state;    //-1 for not yet tested, 0 for true, 1 for false, 2 for unknown
};
// //

 

unsigned int total_variables = 0;
unsigned int total_clauses = 0;
std::vector<SAT> Expression;
std::vector<int> compResult;

int main() {
	BinaryTree BinTree;

	input_reader();
	BinTree.add_node(1);
	BinTree.add_node(-2);
	BinTree.add_node(3);
	//BinTree.print_stack();
	compare_result(BinTree.get_stack());
	//print_end_status();

return 0;
	
}

void input_reader() {
    ifstream inFile;
    inFile.open("test1.txt");
    int num;
    vector<int> temp;
    if(!inFile) {
        cerr << "Error";
        exit(1);
    } else {
        inFile.ignore(1000,' ');
        inFile.ignore(1000,' ');
        inFile >> total_variables;
        inFile >> total_clauses;
        while(inFile >> num) {
            if(num != 0)
                temp.push_back(num);
            else if(num == 0) {
                read_into_vector(temp);
                delete_temp_vector(temp);
            }
        }
    }
}

void read_into_vector(vector<int> vect)
{
	SAT temp;
	temp.clause = vect;
	temp.state = -1;
	Expression.push_back(temp);
}
void delete_temp_vector(vector<int>& vect)
{
    while(vect.size() != 0) {
        vect.pop_back();
    }
}
void flush_compResult_vector()
{
	while(compResult.size() != 0) {
		compResult.pop_back();
	}
}

void print_end_status(){
	for (int i = 0; i < compResult.size(); i++){
		if (compResult.at(i) != 0){
			cout << endl << "Solution for clause " << i << " not good";
			break;
		}
	}
	cout << endl << "Solution works";
}

void compare_result(vector<int> solution){
	for (int i = 0; i < Expression.size(); i++){ // clause loop
		cout << "i = " << i << endl;
		int solved = 2;
		for (int j = 0; j < Expression.at(i).clause.size(); j++){ // clause var loop
			cout << "j = " << j << endl;
			for (int k = 0; k < solution.size(); k++){ // proposed soln loop 
				cout << "k = " << k << endl;
				if (Expression.at(i).clause.at(j) == solution.at(k)){ // proposed var soln checked good for clause
					compResult.push_back(0);
					Expression.at(i).state = 0;
					break;
				}
				else if (abs(Expression.at(i).clause.at(j)) == abs(solution.at(k))){ // proposed var soln does not work for clause check
						solved = 1;
				}
			}
			if (solved == 0){ // break from clause var loop if soln is good
				break;
			}
		}
		if (solved == 1){ // Proposed var soln fails for this clause
			compResult.push_back(1);
			Expression.at(i).state = 1;
		} else if (solved == 2){ // proposed var soln not applicable to clause
			compResult.push_back(2);
			Expression.at(i).state = 2;
		}
	}
}