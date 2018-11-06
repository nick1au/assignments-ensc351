#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct SAT
{
	vector<int> clause;
	bool verify;
};

struct Solution
{
	int value;
	bool true_false;
};

struct node
{
	int value;
	bool is_solution;
	node* left;
	node* right;
};
vector<node*>* solution_vector = new vector<node*>;
class SolutionTree
{
public:
	SolutionTree()
	{
		node* zero = new node;
		zero->value = 0;
		zero->is_solution = false;
		zero->left = NULL;
		zero->right = NULL;
		root = zero; 
	}
	~SolutionTree()
	{}
	void initial_solution(int num)
	{
		node* add_leaf = new node;
		add_leaf->value = num;
		add_leaf->is_solution = false;
		add_leaf->left = NULL;
		add_leaf->right = NULL;

		node* temp = root;
		while(temp->left != NULL)
		{
			temp = temp->left;
		}
		temp->left = add_leaf;
		temp->right = NULL;
	}

	void intial_backtrack()
	{
		node* tracker = root;
		while(tracker->left != NULL && tracker->right == NULL)
		{
			tracker = tracker->left;
		}
		node* new_leaf = new node;
		new_leaf->value = (-1) * tracker->value;
		add_leaf->is_solution = false;
		new_leaf->left = NULL;
		new_leaf->right = NULL;
		tracker->right = new_leaf;
	}
	void backtracking()
	{
		node* tracker = root;
		while(tracker->left->left != NULL)
		{
			tracker = tracker->left;
		}
		backtracking(tracker);
	}
	void backtracking(node* current)
	{

		node* new_leaf = new node;
		new_leaf->value = (-1) * current->left->value;
		add_leaf->is_solution = false;
		new_leaf->left = NULL;
		new_leaf->right = NULL;
		current->right = new_leaf;
	}

	void preorder_tree(node* temp)
	{
		if(temp == NULL)
			return;
		solution_vector->push_back(temp);
		preorder_tree(temp->left);
		preorder_tree(temp->right);
	} 
	void wrapper()
	{
		node* temp = root;
		preorder_tree(root);
	}

private:
	node* root;
	
};
vector<SAT> Big_Expression;
vector<Solution> Answer;
unsigned int total_variables;
unsigned int total_clauses;


void read_into_vector(vector<int>);
void delete_temp_vector(vector<int>&);
void input_reader();
void display();
void initializing_solution_vector();
void initiate_compare_protocol(Solution&); 
void purpose_solution();
bool checking_solution();
void print_treevector();
void initial_solution_tree(SolutionTree&);
void compare_sol_with_clause_vector(int value, SAT&);

//true == 1   false == 0
int main(){
	input_reader();
	display();
	SolutionTree soltree;

	initial_solution_tree(soltree);
	soltree.wrapper();
	print_treevector();
	cout << endl;
	//display();

	//initializing_solution_vector();
	//purpose_solution();
	if(checking_solution())
		cout << "true";
	return 0;
}
void initial_solution_tree(SolutionTree& tree)
{
	for(unsigned int i = 1; i <= total_variables; i++)
	{
		for(unsigned int j = 0; j < Big_Expression.size(); j++)
		{
			compare_sol_with_clause_vector((int) i, Big_Expression.at(j));
		}
		//cout << temp << endl;
		tree.initial_solution((int) i);
	}
}
void compare_sol_with_clause_vector(int value, SAT& temp)
{
	for(unsigned int i = 0; i < temp.clause.size(); i++)
	{
		//cout << value << "\t" << temp.clause.at(i) << endl;
		if (value == temp.clause.at(i))
		{
			temp.verify = true;
		}
	}
}
void input_reader()
{
	ifstream inFile;
	inFile.open("file.txt");
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
void delete_temp_vector(vector<int>& vect)
{
	while(vect.size() != 0)
	{
		vect.pop_back();
	}
}

// generate number 1 to total variables and push it into the Answer vector.
void initializing_solution_vector()
{
	for (unsigned int i = 1; i <= total_variables; i++)
	{
		Solution sol = {(int) i, false};
		//cout << sol.value << sol.true_false << endl;
		Answer.push_back(sol);
	}
}
//compare the initial variable with the clauses.
void purpose_solution()
{
	for (unsigned int i = 0; i < Answer.size(); i++)
	{
		initiate_compare_protocol(Answer.at(i));
	}
}
bool checking_solution()
{
	for (unsigned int i = 0; i < Big_Expression.size(); i++)
	{
		if(!Big_Expression.at(i).verify)
			return false;
	}
	return true;
}
void initiate_compare_protocol(Solution& sol)
{
	for (unsigned int i = 0; i < Big_Expression.size(); i++)
	{
		for (unsigned int j = 0; j < Big_Expression.at(i).clause.size(); j++)
		{
			if(sol.value == Big_Expression.at(i).clause.at(j))
			{
				Big_Expression.at(i).verify = true;
				//sol.true_false = true;
				//if(temp.verify == false)	
			}
		}
	}
}

void print_treevector()
{
	for(unsigned int i = 0; i < solution_vector->size(); i++)
	{
		node* temp = solution_vector->at(i);
		cout << temp->value;
	}
}

