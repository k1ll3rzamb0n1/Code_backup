#include <iostream>
using namespace std;

int main ()
{
	cout << "Welcome TO My Calculator\n" << endl;
	system ("PAUSE");

	cout << "Please select an operation from the list bellow" << endl;
	int operation;
	do
	{
	cout << "1) Add\n 2) subtract\n 3) multiply\n 4) divide\n 5) compare\n 6) GCD\n 7) Quit\n" << endl;
	cin >> operation;
	if (operation>7)
	{
	
		cout << "You Fail" << endl;
		system ("PAUSE");
	}
	
	else if (operation == 7)
		exit(0);
	else
	{

	
	cout << "select your two values:\n" << endl;
	cout << "value 1:\n" << endl;
	int value1;
	cin >> value1;

	cout << "value 2:\n" << endl;
	int value2;
	cin >> value2;

	int total;
	int nv1 = 11;
	int nv2 = 11;
	int temp = 11;
	

	switch (operation)
	{
	case 1:
		total=value1+value2;
		cout << value1 << "+" << value2 << "=" << total  << endl;
		break;
	case 2:
		total=value1-value2;
		cout << value1 << "-" << value2 << "=" << total  << endl;
		break;
	case 3:
		total=value1*value2;
		cout << value1 << "*" << value2 << "=" << total  << endl;
		break;
	case 4:
		total=value1/value2;
		if (value2==0)
			cout << "Error, undefined" << endl;
		else
		cout << value1 << "/" << value2 << "=" << total << endl;
		break;
	case 5:
		if (value1>value2)
			cout << value1 << " is greater that " << value2 << endl;
		else if (value1<value2)
			cout << value1 << " is less than " << value2 << endl;
		else if (value1==value2)
			cout << value1 << " is equal to " << value2 << endl;
		break;
	case 6:
		if (value1 != 0 && value2 != 0)
			{	
				if (value2 > value1)
				{nv1 = value2;
				nv2 = value1;}
				else
				{nv1 = value1;
				nv2 = value2;}
				do {
				temp = nv1;
				nv1 = nv2;
				nv2 = temp % nv2;
				} while (nv2 >0);

			cout << " The greatest common divisor is " << nv1 << endl; 
			}
		else
			cout << "There is no GCD for zero." << endl;
		break;

	default:
		cout << "cant do that silly. follow the instructions" << endl;
	}
	system ("PAUSE");

	}
	} while (operation != 7);



}