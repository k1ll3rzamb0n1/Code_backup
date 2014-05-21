#ifndef WQUEUE_H
#define WQUEUE_H

#include "word.h"
#include<string>
#include <iostream>

class WQueue
{
private:
	Word* front;
	Word* back;
public:
	WQueue();
	~WQueue();
	WQueue(WQueue& q);

	Word* getFront()
	{
		return front;
	}
	Word* getBack()
	{
		return back;
	}

	void print();

	void insert(string s);

	string remove();

	string peek();

	
};

#endif


