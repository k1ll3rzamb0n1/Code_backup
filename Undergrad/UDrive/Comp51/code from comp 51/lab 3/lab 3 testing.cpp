#include <iostream>
using namespace std;

int main()
{
	// initialize vars
	double price = 0, tender = 0; 
	int change = 0;
	int twenties = 0, tens = 0, fives = 0, ones = 0, quarters = 0, dimes = 0, nickels = 0, pennies = 0;

	// get input from user
	cout << "Please enter sales price: $";
	cin >> price;
	if (price < 0)
		cout << "Can't handle negative prices!!\n";
	else
	{
		cout << "Please enter payment amount: $";
		cin >> tender;

		// calculate each type of change
		if (tender < price)
			cout << "U didnt pay me enough!!\n";
		else
		{

		change = (int)((tender - price) * 100); // change required in pennies
		twenties = change / 2000; // # of twenties to dispense
		change = change % 2000;   // change required after twenties have been dispensed
		tens = change / 1000;
		change = change % 1000;
		fives = change / 500;
		change = change % 500;
		ones = change / 100;
		change = change % 100;
		quarters = change / 25;
		change = change % 25;
		dimes = change / 10;
		change = change % 10;
		nickels = change / 5;
		change = change % 5;
		pennies = change;


		// display results
		cout << "Change dispensed as follows:\n"
			 << twenties << " twenties\n"
	 		 << tens << " tens\n"
			 << fives << " fives\n"
			 << ones << " ones\n"
			 << quarters << " quarters\n"
			 << dimes << " dimes\n"
			 << nickels << " nickels\n"
			 << change << " pennies\n";
	}
	}
	system("PAUSE");
}