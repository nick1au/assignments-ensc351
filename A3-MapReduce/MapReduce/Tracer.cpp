#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <thread>
#include <process.h>
#include "Tracer.h"

using namespace std;

ofstream myFile;		// file to write traces to
int data_counter = 0;	// keep track of how many traces are added

chrono::system_clock::time_point reference_time;	// reference time when tracing starts
chrono::duration<double, micro> start_time_micro;	// a duration since the reference time [microseconds]
chrono::duration<double, micro> end_time_micro;		// a duration since the reference time [microseconds]

thread::id thread_id;
int process_id;

// struct to keep all the values for each trace
struct dataValues {
	string name = "";
	string category = "";
	char phase;
	int pid;
	thread::id tid;
	double time_stamp; // can also set type to 'long'
	
	// struct to keep multiple arguments organized
	struct argument {
		string arg_name;
		double arg_value;
	}arg[1]; // only one argument for now

}my_data[10000]; // allocating space for 10,000 traces



void trace_object::trace_start(char* filename) {
	myFile.open(filename);

	// get tid and pid and reference time
	reference_time = chrono::system_clock::now();
	thread_id = this_thread::get_id();
	process_id = _getpid();

}

void trace_object::trace_end() {
	// call trace_flush to output to a file
	trace_flush();
}

void trace_object::trace_event_start(char* name, char* category, char* arguments) {

	start_time_micro = (chrono::system_clock::now() - reference_time);
	
	// removing cout in trace_event_start will make the end time expand a bit more rather than going up in a straight line.
	//cout << start_time_micro.count() << endl;

	my_data[data_counter].name = name;
	my_data[data_counter].category = category;
	my_data[data_counter].phase = 'B';
	my_data[data_counter].tid = thread_id;
	my_data[data_counter].pid = process_id;
	my_data[data_counter].time_stamp = start_time_micro.count();

	// need to check for multiple arguments 
	// my_data[data_counter].arg[0].arg_name = arguments;

	data_counter++;
}

void trace_object::trace_event_end(char* arguments) {

	end_time_micro = (chrono::system_clock::now() - reference_time);

	my_data[data_counter].name = "";
	my_data[data_counter].category = "";
	my_data[data_counter].phase = 'E';
	my_data[data_counter].tid = thread_id;
	my_data[data_counter].pid = process_id;
	my_data[data_counter].time_stamp = end_time_micro.count();

	// need to check for multiple arguments 

	data_counter++;
}

void trace_object::trace_instant_global(char* name) {

	start_time_micro = (chrono::system_clock::now() - reference_time);

	my_data[data_counter].name = name;
	my_data[data_counter].category = "";
	my_data[data_counter].phase = 'i';
	my_data[data_counter].tid = thread_id;
	my_data[data_counter].pid = process_id;
	my_data[data_counter].time_stamp = start_time_micro.count();

	data_counter++;
}

void trace_object::trace_counter(char* name, char* key, double value) {

	start_time_micro = (chrono::system_clock::now() - reference_time);

	my_data[data_counter].name = name;
	my_data[data_counter].category = "";
	my_data[data_counter].phase = 'C';
	my_data[data_counter].tid = thread_id;
	my_data[data_counter].pid = process_id;
	my_data[data_counter].time_stamp = start_time_micro.count();

	my_data[data_counter].arg[0].arg_name = key;
	my_data[data_counter].arg[0].arg_value = value;

	data_counter++;
}

void trace_object::trace_flush() {
	myFile << "[\n";

	for (int i = 0; i <= data_counter; i++) {
		if (i != data_counter) {
			if (my_data[i].phase == 'B') {
				myFile << "{ \"name\": \"" << my_data[i].name << "\","
					<< " \"cat\": \"" << my_data[i].category << "\","
					<< " \"ph\": \"" << my_data[i].phase << "\","
					<< " \"pid\": " << my_data[i].pid << ","
					<< " \"tid\": " << my_data[i].tid << ","
					<< " \"ts\": " << my_data[i].time_stamp << "},\n";
				// can check for arguments here
			}

			else if (my_data[i].phase == 'E') {
				myFile << "{ \"ph\": \"" << my_data[i].phase << "\","
					<< " \"pid\": " << my_data[i].pid << ","
					<< " \"tid\": " << my_data[i].tid << ","
					<< " \"ts\": " << my_data[i].time_stamp << "},\n";
				// can check for arguments here
			}

			else if (my_data[i].phase == 'i') {
				myFile << "{ \"name\": \"" << my_data[i].name << "\","
					<< " \"ph\": \"" << my_data[i].phase << "\","
					<< " \"pid\": " << my_data[i].pid << ","
					<< " \"tid\": " << my_data[i].tid << ","
					<< " \"ts\": " << my_data[i].time_stamp << ","
					<< " \"s\": \"g\"},\n";
			}

			else if (my_data[i].phase == 'C') {
				myFile << "{ \"name\": \"" << my_data[i].name << "\","
					<< " \"ph\": \"" << my_data[i].phase << "\","
					<< " \"pid\": " << my_data[i].pid << ","
					<< " \"tid\": " << my_data[i].tid << ","
					<< " \"ts\": " << my_data[i].time_stamp << ","
					<< " \"args\": {\"" << my_data[i].arg[0].arg_name << "\":"
					<< my_data[i].arg[0].arg_value << "}},\n";
				// need to be able to check for multiple counters
			}
			else {
				cout << "Unknown phase ID.\n";
				break;
			}
		}
		else {
			myFile << "{}\n]";
		}
	}
	myFile.close();
	cout << "Flush complete.\n";

}