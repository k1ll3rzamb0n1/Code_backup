#ifndef WQUEUE_H
#define WQUEUE_H

#include "word.h"
#include <iostream>
using namespace std;

class WQueue
{
protected:
	Word *front;
public:
	WQueue();
	WQueue(WQueue& toCopy);
	~WQueue();
	void print();
	void insert(string s, int p);
	string remove();
	string peek();
};

#endif