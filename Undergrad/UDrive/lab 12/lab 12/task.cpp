#include "task.h"
#include <iostream>
using namespace std;

Task::Task(string s, int p)
{
	task = s;
	priority = p;
}

int Task::getPriority()
{
	return priority;
}

string Task::getTask()
{
	return task;
}

void Task::setPriority(int p)
{
	priority = p;
}

void Task::setTask(string s)
{
	task = s;
}

void Task::print()
{
	cout << "{ " << priority << " - " << task << " } ";
}

