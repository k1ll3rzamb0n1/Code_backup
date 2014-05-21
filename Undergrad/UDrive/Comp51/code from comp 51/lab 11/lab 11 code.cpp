# include <iostream>
# include <string>
using namespace std;

struct Fencer
{
	string name;
	string weapon;
	int score1;
	int score2;
};

void getTeam(Fencer aray[], int size)
{
	for (int i = 0; i<size ; i++)
	{
		cout << "INFO FOR FENCER #" << (i+1) << endl;
		cout << "What is fencer " << (i+1) << "'s name? : ";
		cin >> aray[i].name;
		cout << "\nWhat weapon does fencer " << (i+1) << " use? : ";
		cin >> aray[i].weapon;
		cout << "What are fencer " << (i+1) << "'s scores? : ";
		cin >> aray[i].score1 >> aray[i].score2;
	}
}
void printTeam(Fencer aray[], int size)
{
	for (int a = 0; a < size; a++)
	{
		cout << aray[a].name << " ";
		cout << aray[a].weapon << " ";
		if (aray[a].score1 > aray[a].score2)
			cout <<": " << aray[a].score1 << endl;
		else
			cout <<": " << aray[a].score2 << endl;
	}
}

void weaponChoice(Fencer aray[], int size)
{
	string choice;
	cout << "Please select a weapon? :";
	cin >> choice;
	cout << endl;

	for (int b = 0; b<size ; b++)
	{
		if (aray[b].weapon == choice)
			cout << aray[b].name << endl;
	}
}

int main ()
{
	Fencer team[5];

	getTeam(team,5);
	printTeam(team,5);
	weaponChoice(team,5);

	system ("PAUSE");
}