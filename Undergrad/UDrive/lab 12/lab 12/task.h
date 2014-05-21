#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

class Task
{
protected:
	int priority;
	string task;
public:
	Task(string s = "None", int p = -99);
	int getPriority();
	string getTask();
	void setPriority(int p);
	void setTask(string s);

	void print();
};

#endif