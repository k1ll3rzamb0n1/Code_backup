# include <iostream>

using namespace std;

void find (char letters[], int size, char c)
{
	bool g = false;
for (int a = 0; a < size; a += 1)
{
	if ( c == letters[a])
	{ 
		cout << " found " << c << " at position " << a << " ." << endl;
		g = true;
	}
}
if ( g == false)
{
	cout << "Your letter did not exist in this word" << endl;
}
}

int main ()
{
	char word [8];

for (int i = 0; i < 8; i += 1)
{
	cout << "Please enter letter #"<<i<<": ";
	cin >> word [i];
}
cout << " the word is ";
for (int t = 0; t < 8; t+=1)
{
	cout <<word[t];
	
}
cout << "\nthe word backwards is ";
for (int x = 7; x>=0; x-=1)
{
	cout  << word [x];
}
cout << endl;
char pick;
cout << "Please pick a character you would like to know the spot for?" << endl;
cin >> pick;

find (word, 8, pick);

system ("PAUSE");
}