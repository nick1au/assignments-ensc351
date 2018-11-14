#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // std::min_element, std::max_element
#include <cmath>

using namespace std;

unsigned int total_variables = 0;
unsigned int total_clauses = 0;
bool no_solution = false;

struct SAT {
	std::vector<int> clause;
	int state;    //0 for true, 1 for false, 2 for unknown
};

struct Node
{
	int value;
	Node* left;
	Node* right;
};

std::vector<SAT> Expression; //vector of struct for the input file
std::vector<int> CompResult; //vector of int for comparing with the purposed variable.
class BinaryTree
{
private:
	Node* root;
	std::vector<Node*> stack;
public:
	BinaryTree()
	{
		root = creating_new_node(0);
		stack.push_back(root);
	}
	~BinaryTree()
	{}
	Node* creating_new_node(int i)
	{
		Node* new_node = new Node;
		new_node->value = i;
		new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}
	void add_node(int i, Node* current)
	{
		Node* new_node = creating_new_node(i);
		if(i > 0)
			current->left = new_node;
		else 
			current->right = new_node;
		stack.push_back(new_node);
	}
	void adding_solution_to_tree()
	{
		int counter = 1;
		while(counter <= total_variables && !no_solution)
		{
			if(is_variable_true(counter))
			{
				add_node(counter, stack.at(stack.size()-1));
				counter++;

			}
			else if(is_variable_true(-1 * counter))
			{
				add_node(-1*counter, stack.at(stack.size()-1));
				counter++;
			}
			else 
			{
				backtracking();
				counter = stack.at(stack.size()-1)->value;
				
			}	

		}
	}
	void backtracking()
	{
		bool solution = true;
		Node* current_node = stack.at(stack.size()-1);
		stack.pop_back();
		if(current_node->value > 0)
		{
			Node* previous_node = stack.at(stack.size()-1);
			Node* new_node = new Node;
			new_node->value = (-1 * (current_node->value));
			new_node->left = NULL;
			new_node->right = NULL;
			stack.push_back(new_node);
		}
		else
		{
			while(current_node->value < 0 && solution)
			{
				current_node = stack.at(stack.size()-1);
				stack.pop_back();
				if(current_node->value = -1)
					solution = false;
			}
			if(solution)
			{
				Node* previous_node = stack.at(stack.size()-1);
				Node* new_node = new Node;
				new_node->value = (-1 * (current_node->value));
				new_node->left = NULL;
				new_node->right = NULL;
				stack.push_back(new_node);
			}
		}
		if(solution == false)
			no_solution = true;

	}

	bool is_variable_true(int num)
	{
		for(unsigned int i = 0; i < Expression.size(); i++)  //loop for the vector of struct
		{
			for(unsigned int j = 0; j < Expression.at(i).clause.size(); j++) //loop for the each indivindual clause
			{
				if(Expression.at(i).state == 2)
				{
					if((abs(num) == Expression.at(i).clause.at(j)) || (num == abs(Expression.at(i).clause.at(j))))
					{
						if(num * Expression.at(i).clause.at(j) > 0)
							Expression.at(i).state = 0;
						else if(finding_max(Expression.at(i).clause) <= abs(num)) //no more variables remain as this results in false condition.
							Expression.at(i).state = 1; // need to backtrack as this variable won't be the solution.
					}
				}

			}
		}
		//finding any false statement becuase of this purposed number
		for(unsigned int i = 0; i < Expression.size(); i++)
		{
			if(Expression.at(i).state == 1)
				return false;
		}
			return true;
	}	

	int finding_max(vector<int> vect)
	{
		vector<int>::iterator result;
		for(unsigned int i = 0; i < vect.size(); i++)
		{
			vect.at(i) = abs(vect.at(i));
		}
		result = std::max_element(vect.begin(), vect.end());
		return vect.at(distance(vect.begin(), result));
	}
	void display_solution()
	{
		if(no_solution)
			cout << "No solution";
		else
		{
			for(unsigned int i = 1; i < stack.size(); i++)
			{
				cout << stack.at(i)->value;
			}
		}
	}
		
};
void input_reader();
void read_into_vector(vector<int> vect);
void delete_temp_vector(vector<int>& vect);
void flush_compResult_vector();

int main() {
	BinaryTree SATSolution;
	input_reader();
	SATSolution.adding_solution_to_tree();
	SATSolution.display_solution();

return 0;
	
}

void input_reader() 
{
    ifstream inFile;
    inFile.open("test1.txt");
    int num;
    vector<int> temp;
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
        while(inFile >> num) 
        {
            if(num != 0)
                temp.push_back(num);
            else if(num == 0) 
            {
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
	temp.state = 2; //since the clause is initially at unknown state
	Expression.push_back(temp);
}
void delete_temp_vector(vector<int>& vect)
{
    while(vect.size() != 0) 
    {
        vect.pop_back();
    }
}
void flush_CompResult_vector()
{
	while(CompResult.size() != 0) 
	{
		CompResult.pop_back();
	}
}