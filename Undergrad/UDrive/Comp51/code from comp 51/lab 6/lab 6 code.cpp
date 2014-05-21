# include <iostream>
# include <iomanip>
using namespace std;

int main()
{
	double balance;
	double startingbalance;
	double intrestrate;
	double annualcontribution;
	double years;
	cout << "Please enter the starting balance for your account: ";
	cin >> balance;
	startingbalance=balance;
	cout << "Please enter the intrest rate your account will earn: ";
	cin >> intrestrate;
	cout << "Please enter your projected annual contribution for the account: ";
	cin >> annualcontribution;
	cout << "How manty years do you plan to keep the account: ";
	cin >> years;

	cout.setf(ios::fixed);
	cout.precision (2);
	
	for ( int row=1; row <= years; row++)
	{
		balance = balance * (1 +intrestrate / 100) + annualcontribution;

	}
cout << " Your ballance after " << years << " will be: "<< balance << endl;

system ("Pause");

cout <<""<<setw(10)<< "Rate" << setw(10) << "5 years" << setw(10) << "10 years" << setw(10) << "15 years" << setw(10) << "20 years" << setw(10) << "25 years" << setw(10) << "30 years" << setw(10) << endl;
for (double row=3; row<=10; row+=.5)
{
	cout << row << setw(10);
	for ( int col = 5; col <= 30; col += 5)
	{
		startingbalance = startingbalance * (1 + row / 100) + annualcontribution;
		cout << startingbalance << setw(10);

	}
	cout << endl;
}

system ("PAUSE");





}