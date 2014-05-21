//Ryan Bleile, Project 1
# include <iostream>
using namespace std;
# include <ctime>

int main ()
{
	cout << "Welcome to the Number Guessing Game!!\n" << endl;
	system ("PAUSE");

	cout << "\nI have chosen a certain number that is between one and ten.\n Can you guess it?\n" << endl;
	system ("PAUSE");

	srand(time(0)); 
	int numberToGuess; 
	numberToGuess = rand()%10 + 1;

	cout << "What is your first guess?\n" << endl;

	double theGuess;
	cin >> theGuess;

	if (theGuess>numberToGuess)
		cout << "You Guessed to HIGH silly, Guess again.\n" << endl;
	else if (theGuess<numberToGuess)
		cout << "You Guessed to LOW! Now u gotta Guess again.\n" << endl;
	else if (theGuess==numberToGuess)
	{cout << " OH!! U got me. Victory is yours!!!" << endl;
		system ("PAUSE");
		exit (0);
	}
	cout << "What is your second Guess?\n" << endl;
	double theGuess2;
	cin >> theGuess2;

	if (theGuess2>numberToGuess)
		cout << "You Guessed to HIGH silly, Guess again.\n" << endl;
	else if (theGuess2<numberToGuess)
		cout << "You Guessed to LOW! Now u gotta Guess again.\n" << endl;
	else if (theGuess2==numberToGuess)
	{cout << " OH!! U got me. Victory is yours!!!" << endl;
		system ("PAUSE");
		exit (0);
	}
	cout << "Last chance boyo, what is your third guess?\n" << endl;
	double theGuess3;
	cin >> theGuess3;

	if (theGuess3>numberToGuess)
		cout << "You Guessed to HIGH silly,Now u just FAIL, HAHAHA U cant defeat me!\n Im the super number guessing game!!.\n" << endl;
	else if (theGuess3<numberToGuess)
		cout << "You Guessed to LOW! Now u just FAIL, HAHAHA U cant defeat me!\n Im the super number guessing game!!.\n"  << endl;
	else if (theGuess3==numberToGuess)
	{	cout << " OH!! U got me. Victory is yours!!!" << endl;
		system ("PAUSE");
		exit (0);
	}
	system ("PAUSE");
	cout << "well you couldnt guess my number so ill tell you, it was " << numberToGuess << "." << endl;
	system ("PAUSE");






}