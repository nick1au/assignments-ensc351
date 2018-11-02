#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>

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

class ClauseList
{
private:
	Node* head = NULL;
	Node* tail = NULL;
public:
	~ClauseList()
	{
		Node* to_delete = new Node;
		to_delete = head;
		while(head != NULL)
		{
			delete to_delete;
			head = head->next;
			to_delete = head;
		}
		
	}
	void createfirstnode(string str)
	{
		Node* temp = new Node;
		temp->value = str;
		temp->unknown = false;
		temp->true_false = false;
		temp->next = NULL;
		head = temp;
		tail = temp;
	}
	void createNode(string str)
	{
		Node* temp = new Node;
		temp->value = str;
		temp->unknown = false;
		temp->true_false = false;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
	void display()
	{
		Node* temp = new Node;
		temp = head;
		while(temp != NULL)
		{
			cout << temp->value << endl;
			temp = temp->next;
		}
		
	}

	/* data */
};

ClauseList listofclause;
string variable;
string clauses;
void input_reader();

int main(){
	
	input_reader();
	listofclause.display();

	return 0;
}

void input_reader()
{
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
		inFile >> variable;
		inFile >> clauses;
		inFile >> str;
		listofclause.createfirstnode(str);
		while(inFile >> str)
		{
			listofclause.createNode(str);
		}
	}

}




