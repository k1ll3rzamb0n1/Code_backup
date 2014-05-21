#include "heap.h"

int main()
{
// Once your heap functions are written you can use the following code to test it or write your own.

	int size = 0;
	Heap h;
	int p;
	string s;

	cout << "Enter number of tasks: ";
	cin >> size;
 
	for (int i = 0; i < size; i++)
	{
		cout << "Enter priority level of task " << i << ": ";
		cin >> p;
		cout << "Enter description of task " << i << ": ";
		cin.ignore();
		getline(cin, s);
		Task temp(s,p);
		h.insert(temp);
	}

	h.print();

	for (int i = 0; i < size; i++)
		cout << "Popping: " << h.pop().getTask() << endl;

	system("PAUSE");
}