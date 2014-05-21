/*****************************************************************************
 *  Filename: stringlab.cpp
 *  Author: 
 *  Description: Our very own string class with most of the functionality of
 *               the C++ string class and lots of pointers.
 *               For this lab you need to complete the implementation of the
 *               following functions:
 *               Easy To Write:
 *               - charAt()
 *               - print()
 *               More Thought Required:
 *               - isPalindrome()
 *               - substring()
 *               - operator + (concatenation)
 ****************************************************************************/
#include <iostream>
using namespace std;

/* Class: String
 * Description: A string class implemented as a character array that implements
 *              all of the standard string functions: constructors, getLength,
 *              charAt, print, reverse, isPalindrome, substring.
 */
class String
{
private:
	char* word;
	int length;
public:
	/* Function: default constructor
	 * Description: A constructor that asks the user how long the string will
	 *              be and then prompts them for the string.
	 */
	String()
	{	
		// Prompt for the length and create an appropriately sized char array.
		cout << "Please enter the number of characters in your string: ";
		cin >> length;
		word = new char [length];

		// Read in the string one letter at a time
		cout << "Please enter your string: ";
		for (int i = 0; i < length; i++)
			cin >> word[i];
	}
	/* Function: general constructor
	 * Description: A constructor that converts an existing character array into
	 *              a String object.
	 */
	String (char* c, int l)
	{
		word = c;
		length = l;
	}
	/* Function: getWord()
	 * Description: returns a pointer to the character array storing the word
	 */
	char* getWord()
	{
		return word;
	}
	/* Function: getLength()
	 * Description: returns the length of the string.
	 */
	int getLength() 
	{
		return length;
	}
	/* Function: charAt()
	 * Description: returns the ith character in the string
	 */
	char charAt(int i) 
	{
		return word[i];
	}
	/* Function: print()
	 * Description: displays the string to the screen.
	 */
	void print() 
	{
		for(int i = 0; i < length; i++)
			cout << word[i];
		cout << endl;
		return;
	}

	/* Function: reverse
	 * Description: Reverses the order of the letters in the string.
	 */
	void reverse()
	{
		// Initialize pointers to read forward and backward through the string.
		char* forward = word;
		char* backward = word + length - 1;
		char temp; // temp var for swapping
		// Move the pointers toward each other, swapping the letters as they go.
		while (backward > forward)
		{
			temp = *backward;
			*backward = *forward;
			*forward = temp;
			backward--;
			forward++;
		}
	}
	/* Function: isPalindrome()
	 * Description: tests whether the word stored in the char array is a palindrome, i.e.
	 *              reads the same forwards and backwards.
	 */
	bool isPalindrome()
	{
		char* forward = word;
		char* backward = word + length -1;
		bool test = true;

		while(backward > forward && test)
		{
			if (*backward == *forward)
				test = true;
			if (*backward != *forward)
				test = false;
			backward--;
			forward++;
		}
		return test;
	}
	/* Function: substring()
	 * Description: creates a new array with just the letters between start and stop inclusive
	 *              and returns the new array.
	 */
	char* substring(int start, int stop)
	{
		int l = start - stop + 1;
		char* nwWord = new char [l];
		for ( int y = start;  y <= stop; y++)
		{
			nwWord[y - start] = word[y];
		}
		return nwWord;
	}
		
};

/* Overload: ==
 * Description: Overloads the == operator to handle String objects.
 */
const bool operator == (String s1, String s2)
{
	// If different legnths, not the same word
	if (s1.getLength() != s2.getLength())
		return false;
	// Access the character arrays
	char* ptr1 = s1.getWord();
	char* ptr2 = s2.getWord();
	// Compare letter by letter, if they differ in one letter,
	// then not the same word
	for (int i = 0; i < s1.getLength(); i++)
		if (*(ptr1+i) != *(ptr2+i))
			return false;
	// Otherwise the strings are the same
	return true;
}

/* Overload: +
 * Description: Overloads the + operator to concatenate String objects.
 */
const String operator + (String s1, String s2)
{
	cout << "I still need to be written!!\n";
	return s1;
}

/* Function: handleChoice
 * Description: Takes a valid menu choice and calls the appropriate member functions.
 */
void handleChoice (String s, int c)
{
	// 1. Print String
	if (c == 1)
	{
		cout << "You created the string ";
		s.print();
		cout << endl;
	}
	// 2. Reverse String -- print result
	else if (c == 2)
	{
		s.reverse();
		cout << "The string is now ";
		s.print();
		cout << endl;
	}
	// 3. Create a Substring
	else if (c == 3)
	{
		// get start and end indexes
		int start, stop;
		cout << "Enter the starting and ending indexes of your string: ";
		cin >> start >> stop;
		// create new String object with the substring
		int len = stop - start + 1;
		char* str = s.substring(start, stop);
		String sub (str, len);
		// print out result
		cout << "The new string is ";
		sub.print();
		cout << endl;
	}
	// 4. Palindrome Test
	else if (c == 4)
	{
		// Test to see if a palindrome and print corresponding message.
		if (s.isPalindrome())
		{
			s.print();
			cout << " is a palindrome.\n";
		}
		else
		{
			s.print();
			cout << " is not a palindrome.\n";
		}
	}
	// 5. String Comparison
	else if (c == 5)
	{
		// create string to compare to.
		cout << "Creating the comparison string...\n";
		String comp;
		// perform comparison.
		if (s == comp)
			cout << "The strings are the same.\n";
		else
			cout << "The strings are not the same.\n";
	}
	// 6. String Concatenation
	else 
	{
		// create string to concatenate to original.
		cout << "Creating the string to concatenate to your original string...\n";
		String extra;
		// perform concatenation and print result.
		s = s + extra;
		s.print();
	}
}

/* Function: testMenu
 * Description: Prints the menu of options available for manipulating strings,
 *              collects the users choice and validates choice.
 */
void printMenu()
{
	int choice;
	cout << "Creating string ...";
	String s;
	// while user doesn't opt to quit, print option menu
	do
	{
		// print menu
		cout << "1: Print String\n"
			 << "2: Reverse String\n"
			 << "3: Get Substring\n"
			 << "4: Palindrome Test\n"
			 << "5: Compare Strings\n"
			 << "6: Concatenate Strings\n"
			 << "7: Quit\n"
			 << "Please enter your choice: ";
		// get choice
		cin >> choice;
		// validate and handle choice
		if (choice >= 1 && choice <= 6)
			handleChoice(s,choice);
		else if (choice != 7)
			cout << choice << " is not an option on this menu!  Please try again.\n";
	}while (choice != 7);
}

/* Function: Main
 * Description: Simply calls the test menu function to test the String class.
 */
int main ()
{
	printMenu();
	system("PAUSE");
}
