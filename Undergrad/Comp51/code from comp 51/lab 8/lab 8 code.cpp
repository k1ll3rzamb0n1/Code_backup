//Lab 3 Pizza Deals  ryan bleile
# include <iostream>
using namespace std;


void getdeals (double& a, double& b, double& c, double& d)
{
	
	cout << "What is the diameter of Alice's pizza deal?<in inches>: ";
	cin >> a;
	cout << "What is the price of Alice's pizza deal?: ";
	cin >> b;
	cout << "What is the diameter of Bob's pizza deal?<in inches>: ";
	cin >> c;
	cout << "What is the price of Bob's pizza deal?: ";
	cin >> d;
}
double unitPrice (double e, double f)
{
	double area;
	area = 3.14*(e/2.0)*(e/2.0);
	double cpsi;
	cpsi = f/area;
	return cpsi;
}
void printResults (double m, double n, double o, double p)
{
	double alice = unitPrice (m,n);
cout << "$" << alice << " per square inch" << endl;
	double bob = unitPrice (o,p);
cout << "$" << bob << " per squaer inch" << endl;

if (alice < bob)
	cout << "Alice is a better deal!!!!\n";
else if (bob < alice)
	cout << "Bob is a better deal!!!!!\n";
else
	cout << "They are identical!!";
}



int main ()
{
double aliceDiameter, alicePrice, bobDiameter, bobPrice;

getdeals (aliceDiameter, alicePrice, bobDiameter, bobPrice);

printResults (aliceDiameter, alicePrice, bobDiameter, bobPrice);

system ("PAUSE");


}