#include "WQueue.h"
#include "Word.h"
#include <iostream>
#include <string>

using namespace std;


int main()
{
	WQueue q;
	q.insert("Hi");
	q.insert("my");
	q.insert("name");
	q.insert("is");
	q.insert("BOB");
	q.print();

	WQueue Q = q;
cout << "\n\n\n\n";
	q.remove();
	q.print();

	cout << "\n\n\n\n\n";

	cout << q.peek();

	cout << "\n\n\n\n";
	q.~WQueue();

	cout << "\n\n\n\n";
	q.print();

	cout << "blah \n\n";

	Q.print();




	system("PAUSE");
}