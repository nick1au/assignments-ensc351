#pragma once
class trace_object {
public:
	void trace_start(char* filename);

	void trace_end();

	void trace_event_start(char* name, char* category, char* arguments);

	void trace_event_end(char* arguments);

	void trace_instant_global(char* name);

	void trace_counter(char* name, char* key, double value);

	void trace_flush();
};