#include <iostream>
#include "CharArray.h"
using namespace std;

int main()
{
	CharArray p("Long");
	CharArray l("treasure");

	p.selectionSort();
	p.print();
	cout << endl << endl;

	l.print();
	cout << endl<<endl;
	int s = l.getSize() -1;
	l.quickSort(0,s);

	cout << endl;
	l.print();
	system("PAUSE");


}
