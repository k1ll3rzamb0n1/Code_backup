#include <iostream>



class String
{
public:
	String();
	char* getWord();
	{
		return word;
	}

private:

	char* word;
	int length;

};

String::String()
{
	int length;
	do
	{
	cout << "what is the length?: ";
	cin >> length;
	}while( length <= 0);

	word = new char[lenth];

	cout << "Please enter word: ";
	for(int i = 0; i < length; i++)
		cin >> word[i];
}


bool operator==(String s1, String s2)
{
	if(s1.getLength() != s2.getLength())
		return false;

	char* ptr1 = s1.getWord();
	char* ptr2 = s2.getWord();

	for (int o = 0; o < s1.getLength; o++)
	{
		if (*(ptr1+o)  !=  *(ptr2+o))

			return false;
	}
	return true;
}