#include "templatearray.h"
#include<iostream>
#include<string>

using namespace std;

int main()
{
	Templatearray<char> test;
	system("PAUSE");
	test.addElement('a');
		system("PAUSE");
	test.addElement('b');
		system("PAUSE");
	test.print();
	cout << endl;
		system("PAUSE");
	test.removeElement(0);
		system("PAUSE");
	test.print();
	cout << endl;
		system("PAUSE");
	cout << test.largest() << endl;

	system("PAUSE");
}