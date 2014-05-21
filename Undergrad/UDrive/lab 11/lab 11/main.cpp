#include "tree.h"
#include <ctime>
#include <iostream>
using namespace std;

int main()
{
	srand((unsigned) time);
	Tree t;
	t.addLayer();
	t.print();
	t.~Tree();
	system("PAUSE");
	
	Tree tr;
	tr.insert(50);
	tr.insert(45);
	tr.insert(55);
	tr.insert(10);
	tr.insert(100);

	tr.print();

	system("PAUSE");

	tr.printLeaves();

	system("PAUSE");
	tr.addLayer();
	tr.print();

	system("PAUSE");

}