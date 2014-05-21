#include "WQueue.h"

WQueue::WQueue()
{
	front = NULL;
	back = NULL;
}

WQueue::~WQueue()
{
	string whocares;
	while(front != NULL)
	{
		whocares = remove();
	}

}
WQueue::WQueue(WQueue& q)
{
	Word* cur = q.getFront();
	while ( cur!= NULL)
	{
		insert(cur->getData());
		cur = cur->getNext();
	}
		
}

void WQueue::print()
{
	Word* cur = front;
	while (cur != NULL)
	{
		cout << cur->getData() << " ";
		cur = cur->getNext();
	}
}

void WQueue::insert(string s)
{
	if(front == NULL)
	{
		front = new Word(s);
		back = front;
	}
	else
	{
		Word* cur = back;
		back = new Word(s);
		cur->setNext(back);
	}
}

string WQueue::remove()
{
	if (front == NULL)
	{
		cout << "\n\nempty Q\n\n";
		exit(0);
	}
	else
	{
		Word* cur = front;
		front = front->getNext();
		string whatever = cur->getData();
		delete cur;
		return whatever;

	}
}

string WQueue::peek()
{
	return front->getData();
}

