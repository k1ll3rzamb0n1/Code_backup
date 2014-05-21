#include "word.h"
#include "wqueue.h"

#include <iostream>
#include <string>

using namespace std;


int main()
{
	WQueue q;
	q.insert("BOB", 5);
	q.insert("Charlie", 1);
		system("PAUSE");
	q.print();
		system("PAUSE");
	string what = q.peek();
		system("PAUSE");
	cout <<"\n" << what << endl;
		system("PAUSE");
	q.remove();
		system("PAUSE");
	q.print();
		system("PAUSE");
	WQueue Q;
	Q = q;
		system("PAUSE");
	Q.print();
	system("PAUSE");


}