#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


class BinaryTree
{
private:
	struct Node
	{
		int value;
		Node* left;
		Node* right;
	};
	Node* root;
	
	vector<Node*> stack;
public:
	struct SAT {
	std::vector<int> clause;
	int state;    //-1 for not yet tested, 0 for solved, 1 for not a solution, 2 for not yet solved
};
//
	BinaryTree(){
		Node* new_node = new Node;
		new_node->value = 0;
		new_node->left = NULL;
		new_node->right = NULL;
		root = new_node;
		stack.push_back(new_node);
	}
	~BinaryTree()
	{}

	void add_node(int num)
	{
		Node* new_node = new Node;
		new_node->value = num;
		new_node->left = NULL;
		new_node->right = NULL;
		if (num > 0) { // postive variable, push to the desired tail end of the node of the stack
			stack.at(stack.size()-1)->left = new_node;
		} else if (num < 0) {
			stack.at(stack.size()-1)->right = new_node;
		}
		stack.push_back(new_node);
	}
	vector<int> get_stack(){
		vector<int> solution;
		for (int i = 1; i < stack.size(); i++){  // skip the placeholder at the front of the vector
			solution.push_back(stack.at(i)->value);
		}
		return solution;
	}

	void print_stack(){
		for (int i = 1; i < stack.size(); i++){ // skip the placeholder at the front of the vector
			cout << endl << "i = " << i << " | " << stack.at(i)->value;
		}
	}

	void remove_node_from_stack(){
		stack.pop_back();
	}
	/*
	void compare_result(vector<int> &compResult, vector<SAT> Expression){
		for (int i = 0; i < Expression.size(); i++){ // clause loop
			int solved = 2;
			for (int j = 0; j < Expression.at(i).clause.size(); j++){ // clause var loop
				for (int k = 0; k < stack.size(); k++){ // proposed soln loop
					if (Expression.at(i).clause.at(j) == stack.at(k)->value){ // proposed var soln checked good for clause
						compResult.push_back(0);
						Expression.at(i).state = 0;
						break;
					}
					else if (abs(Expression.at(i).clause.at(j)) == abs(stack.at(k)->value)){ // proposed var soln does not work for clause check
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
	}*/
};
