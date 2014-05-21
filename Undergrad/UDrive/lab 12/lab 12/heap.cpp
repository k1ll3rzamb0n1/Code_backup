#include "heap.h"

/***** Accessors for Indices and Elements *****/

int Heap::parentInd(int index) { return index / 2; }
int Heap::lChildInd(int index) { return 2 * index; }
int Heap::rChildInd(int index) { return 2 * index + 1; }

Task Heap::parent(int index) { return elements[index/2]; }
Task Heap::lChild(int index) { return elements[2 * index]; }
Task Heap::rChild(int index) { return elements[2 * index + 1]; }

int Heap::lastInd() {return elements.size() - 1; }

// Constructor
Heap::Heap()
{
	Task dummy;  // dummy 0th item
	elements.push_back(dummy);
}

void Heap::print()
{
	for(int i = 1; i < elements.size(); i++)
	{
		elements[i].print();
	}
}

void Heap::insert(Task item)
{
	elements.push_back(item);
	int index = elements.size() -1;

	while (index > 1)
	{
		if(elements[index].getPriority() < elements[parentInd(index)].getPriority())
		{
			swap(elements[index], elements[parentInd(index)]);
		}
		index = parentInd(index);
	}
}

Task Heap::pop()
{

	Task t;
	if(elements.size() == 1)
		return t;
	t = elements[1];
	if(elements.size() == 2)
	{
		elements.pop_back();
		return t;
	}
	elements[1] = elements[lastInd()];
	elements.pop_back();
	fixHeap();
	return t;
}

void Heap::fixHeap()
{
	int index = 1;
	while(true)
	{
		if(lChildInd(index) > lastInd())
		{
			return;
		}
		if(rChildInd(index) <= lastInd() && rChild(index).getPriority() <= lChild(index).getPriority())
		{
			if(elements[index].getPriority() <= rChild(index).getPriority())
			{
				return;
			}
			swap(elements[index], elements[rChildInd(index)]);
			index = rChildInd(index);
		}

	}
}