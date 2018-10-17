// Trace-lib.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdlib.h"
#include <fstream>
#include <cassert>
#include <string>
#include <chrono>

// http://www.cplusplus.com/reference/thread/thread/ tid
// https://msdn.microsoft.com/en-us/library/t2y34y40.aspx?f=255&MSPPError=-2147217396 pid

using namespace std;
using namespace std::chrono;

struct logdata {
	string name = "";
	string cat = "";
	string ph = "";
	string s = "";
	void* id;
	int pid;
	int tid;
	int ts;
};

void trace_start(const char* filename); // char vs const char
void trace_event_start(char* name, char* categories, char* arguments);
void trace_event_end(char* arguments);
void trace_instant_global(char* name);
void trace_object_new(char* name, void* obj_pointer);
void trace_object_gone(char*name, void* obj_pointer);
void trace_counter(char* name, char* key, char* value);
void trace_end();
void write_to_text();
int check_event(int i);
void print_Instant_event(int i);


ofstream filestr;
logdata *myData;
int counter;
int write_state = 0; // 0 never written, 1 written
time_point<system_clock> start*,end*;
/*
int main()
{
	trace_start("file.txt");
	cout << counter << endl;
	//char name = "name";
	//char cat = 'cat';
	//char arg = 'arg;'
	trace_event_start((char*) "name", (char*) "cat", (char*) "arg");
	trace_event_end((char*) "arg");
	write_to_text();
	trace_end();
	cin >> counter;
	return 0;
}*/

void trace_start(const char* filename) {
	filestr.open(filename);
	if (filestr.fail()) {
		cout << "Error opening file." << endl;
		assert(1);
	}

	myData = new logdata[11000]; //allocate stuff
	counter = 0;
}

void trace_event_start(char* name, char* categories, char* arguments) {
	(myData[counter]).name = (string)name;
	(myData[counter]).cat = (string)categories;
	(myData[counter]).ph = "B";
	(myData[counter]).pid = 1;
	(myData[counter]).tid = 1;
	if (counter == 0) {
		start = system_clock::now();
	}
	(myData[counter]).ts = start;
	

	//cout << "name " << (myData[counter]).name << " cat " << (myData[counter]).cat << " ph "<< (myData[counter]).ph << " pid " << (myData[counter]).pid << " tid " << (myData[counter]).tid << endl;
	//cout << "cat " << (myData[counter]).cat << endl;

	//write_to_text();

	counter++;
	//cout << myData[0].name;
}

void trace_event_end(char* arguments) {
	int test_c = counter;
	while (test_c > 0) {
		test_c--;
		if ((myData[test_c]).ph == "B"){
		(myData[counter]).name = (myData[test_c]).name;
		(myData[counter]).cat = (myData[test_c]).cat;
		(myData[counter]).ph = "E";
		(myData[counter]).pid = (myData[test_c]).pid;
		(myData[counter]).tid = (myData[test_c]).tid;
        (myData[counter]).ts = start;
        end = system_clock::now();
	    duration<double> elapsed_seconds = (end - start)/1000; // ms
	    (myData[counter]).ts = elapsed_seconds;
		

		//cout << "name " << (myData[counter]).name << " cat " << (myData[counter]).cat << " ph " << (myData[counter]).ph << " pid " << (myData[counter]).pid << " tid " << (myData[counter]).tid << endl;
		//write_to_text();
		counter++;
		return;
		}
	}
	cout << "trace_event_end not possible since no start";


}

void trace_end() {
	filestr << "]";
	filestr.close();
}

void write_to_text() {
	if (write_state == 0) {
		filestr << "[ ";
		write_state = 1;
	}

	for (int i = 0; i < counter; i++)
	{
		if (check_event(i) == 0)
			print_Instant_event(i);
		else{

			filestr << "{ \"name\" : " << "\"" << myData[i].name << "\","
				<< "\"cat\":" << "\"" << myData[i].cat << "\","
				<< "\"ph\":" << "\"" << myData[i].ph << "\","
				<< "\"pid\":" << "\"" << myData[i].pid << "\","
				<< "\"tid\":" << "\"" << myData[i].tid << "\","
				<< "\"ts\":" << "\"" << myData[i].ts << "\" }" << endl;
		}
	}
}

void print_Instant_event(int i)
{
	filestr << "{ \"name\" : " << "\"" << myData[i].name << "\","
		<< "\"ph\":" << "\"" << myData[i].ph << "\","
		<< "\"ts\":" << "\"" << myData[i].ts << "\" "
		<< "\"pid\":" << "\"" << myData[i].pid << "\","
		<< "\"tid\":" << "\"" << myData[i].tid << "\","
		<< "\"s\":" << "\"" << myData[i].s << "\"}" << endl;
}
int check_event(int i)  //Checking to see if the event is either Instant or Counter
{
	if(myData[i].ph == "i")
		return 0;
	else if(myData[i].ph == "C")
		return 1;
	else
		return -1;
}
void trace_instant_global(char* name)
{
	(myData[counter]).name = (string)name;
	(myData[counter]).ph = "i";
	(myData[counter]).s = "g";
	(myData[counter]).pid = 1;
	(myData[counter]).tid = 1;

	counter++;
}

void trace_object_new(char* name, void* obj_pointer)
{
	(myData[counter]).name = (string)name;
	(myData[counter]).ph = "N";
	(myData[counter]).id = obj_pointer;
	(myData[counter]).pid = 1;
	(myData[counter]).tid = 1;
	(myData[counter]).ts = 1;
}

void trace_object_gone(char* name, void* obj_pointer)
{
	(myData[counter]).name = (string)name;
	(myData[counter]).ph = "D";
	(myData[counter]).id = obj_pointer;
	(myData[counter]).pid = 1;
	(myData[counter]).tid = 1;
	(myData[counter]).ts = 1;
}

void trace_counter(char* name, char* key, char* value)
{

}