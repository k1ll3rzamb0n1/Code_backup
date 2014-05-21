#ifndef HEAP_H
#define HEAP_H

#include "task.h"
#include <iostream>
#include <vector>
using namespace std;

class Heap
{
protected:
	vector<Task> elements;

	int parentInd(int index);
	int lChildInd(int index);
	int rChildInd(int index);
	Task parent(int index);
	Task lChild(int index);
	Task rChild(int index);
	int lastInd();

public:
	Heap();

	void print();
	void insert(Task item);
	Task pop();
	void fixHeap();
};

#endif
