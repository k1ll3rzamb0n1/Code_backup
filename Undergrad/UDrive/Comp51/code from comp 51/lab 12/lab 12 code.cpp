# include <iostream>
# include <string>
using namespace std;

class Account
{
public:
	Account();
	Account(string m, double n, double b);
	string getName ();
	double getBalance();
	double getRate ();
	void setName (string m);
	void setBalance (double n);
	void setRate (double b);
	void update();
	void print ();

private:
string name;
double balance;
double intrest;
};

Account::Account()
{
	name = "None";
		balance = 0;
		intrest = 0;
}
Account::Account (string m, double n, double b)
{
	name = m;
	balance = n;
	intrest = b;
}
string Account::getName()
{
	return name;
}
double Account::getBalance()
{
	return balance;
}
double Account::getRate()
{
	return intrest;
}
void Account::setName (string m)
{
	name = m;
}
void Account::setBalance (double n)
{
	balance = n;
}
void Account::setRate(double b)
{
	intrest = b
}
void Account::update()
{
	balance = balance * (1 + intrest);
}
void print()
{
	cout << "Name: " << name << endl << "Balance: " << balance << endl << "Rate :" << intrest << endl;
}


int main ()
{
Account a;
a.print();

Account s = ("bob", 100, .1);
s.print ();
s.update ();
s.print ();
system ("PAUSE");

}