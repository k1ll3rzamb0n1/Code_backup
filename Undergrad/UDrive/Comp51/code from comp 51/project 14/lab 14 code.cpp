# include<iostream>
# include <fstream>

using namespace std;



void append()
{
	char check;
	do
	{
	getData();
	cout << "are there more students to add? <y,n>" << endl;
	cin >> check;
	}while ( check == 'n' || check == 'N');
}
void getData()
{
	int month;
	double testScore;

			cout << "Please input the month the student was born <numerically>" << endl;
			cin >> month;
			cout << "What is the students test score?" << endl;
			cin >> testScore;	
			out << month << " " << testScore << endl;
}
void displaymenu()
{
	cout << "1. Ceate new data file\n2. Append to exhisting data file\n3. Analyze data\n4. Quit" << endl;
}

string namefile()
{
	ofstream out;
	string name;
	 cout << "please enter file name" << endl;
	 cin >> name;
	 out.open(name.c_str());
}
int main()
{
bool go = true;

	do
	{
	displaymenu();
	int menu;
	cin >> menu;
	switch (menu)
		case 1: namefile();
			break;
		case 2: 
			out.open(filename.c_str(),ios::app);
			append();
			out.close();

			break;
		case 3: //analyze();
			break;
		case 4:
			go = false;
			break;
		default;
			break;

	} while (go == true);
}
