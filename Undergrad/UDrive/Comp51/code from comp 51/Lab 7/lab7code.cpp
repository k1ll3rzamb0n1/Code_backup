#include <iostream>
#include <iomanip>
using namespace std;


/* Function:    inflation
 * Description: Prompts the user for the old and new prices of an item and
 *              calculates the rate of inflation: (new - old) / old
 * Returns:     a double representing the rate of inflation
 */
double inflation()
{
	double oldprice;
	double newprice;
	double inflation_rate;
	cout << "What was the old price?: ";
	cin >> oldprice;
	cout << "Ans what is the new price?: ";
	cin >> newprice;

	inflation_rate = (newprice - oldprice) / oldprice;

	return inflation_rate;
}

/* Function:    projection
 * Description: Prompts the user for the current price of an item as well
 *              as the rate of inflation and years until purchase.  It then
 *              calculates & displays the future price of the item:
 *              future price = current * (1 + rate * years)
 * Returns:     nothing
 */

void projection ()
{
	double current;
	double future;
	double rate;
	double years;

	cout << "What is the current price of the item?: ";
	cin >> current;
	cout << "What is the rate of inflation <in decimals> ?: ";
	cin >> rate;
	cout << "How many years until you purchase this item?: ";
	cin >> years;

	future = current * (1 + (rate * years));

	cout << "you will end up paying " << future << " in the future.\n";
}



/* Function:    main
 * Description: Displays a menu of options to the user and then calls functions
 *              to do the appropriate calculations.  Repeats until the user quits.
 */
int main()
{
	int choice;  // variable to store the user's menu choice
	// keep displaying the menu until the user elects to quit
	do
	{
		// display menu and get choice
		cout << "Please pick a menu option:\n"
			 << "1) Calculate Inflation\n"
			 << "2) Calculate Projected Price\n"
			 << "3) Quit\n";
		cin >> choice;

		// handle the different menu options
		if (choice == 1)
		{
			double rate = inflation();
			cout.setf(ios::fixed);
			cout.precision(2);
			cout << "The rate of inflation is " << rate << " or " << (rate * 100) << "%\n\n";
		}
		else if (choice == 2)
		{
			projection ();
		}
		else if (choice != 3)
			cout << "Invalid choice, please try again!\n\n";

	} while (choice != 3);
}
