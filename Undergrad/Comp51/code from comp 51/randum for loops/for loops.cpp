# include <iostream>
using namespace std;

int main()
{

for ( double count = 10; count >= 1; count--)
{
	cout << count << endl;
}

system ("PAUSE");



for ( double count = 0; count <= 1; count +=.1)
{
	cout << count << endl;
}

system ("PAUSE");


int x;
do
{
cout << " input even value to count to" << endl;
cin >> x;
} while (x%2 !=0 );

for ( double count=0; count <= x; count += 2)
{
	cout << count << endl;
}

system ("PAUSE");


for (double count = 1; count <= 1024; count += count)
{
	cout << count << endl;
}
system ("PAUSE");

double total = 0, average, score;

for (int count = 0; count < 10; count++)
{
	cout << "enter score" << endl;
	cin >> score;
	total = total + score;
}

average = total / 10;

cout << average << endl;

system ("PAUSE");

}