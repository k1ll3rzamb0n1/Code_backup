#include "WQueue.h"

// Default Constructor
WQueue::WQueue()
{
	front = NULL;
	
}
	
// Copy Constructor
WQueue::WQueue(WQueue& toCopy)
{
	Word* cur = front;
	Word* other = toCopy.front;
	
	if(cur == NULL)
	{
		return;
	}

	while(cur != NULL)
	{
		other->setNext(new Word(cur->getData(), cur->getPr(), NULL));
		other = other->getNext();
		cur = cur->getNext();
	}
	return;
}

	
// Destructor - repeatedly removes the front item until there are no more
WQueue::~WQueue()
{
	while (front != NULL)
		remove();
}

// Print - displays items separated by newline
void WQueue::print()
{
	Word* ptr = front;
	while (ptr != NULL)
	{
		cout << ptr->getData() << endl;
		ptr = ptr->getNext();
	}
}
	
// Inserts a new item at the back
void WQueue::insert(string s, int p)
{

	Word* cur = front; 

	if (front == NULL) // if list is empty, new item front
	{
		front = new Word(s,p, NULL);
	}
	else if(front->getPr() > p)
	{
			front->setNext(new Word(s,p,cur));
	}
	else
	{	
		
	
		while ( cur->getNext() != NULL && cur->getNext()->getPr() <= p)
		{
			cur = cur->getNext();
		}

		if(cur->getNext() == NULL)
		{
			cur->setNext(new Word(s,p,NULL));
		}
		else 
			cur->setNext(new Word(s,p, cur->getNext()));
	}
		
}
	
// Remove front item and return data from inside the word node.
string WQueue::remove()
{
	if (front == NULL) // if list is empty, return empty string
		return "";
	else // otherwise remove front item, deallocate node and return string from inside
	{
		Word* temp = front;
		string ans = front->getData();
		front = front->getNext();
		delete temp;
		return ans;
	}
}
	
// Peek - return data from inside front node, if it exists.
string WQueue::peek()
{
	if (front == NULL)
		return "";
	else
		return front->getData();
}