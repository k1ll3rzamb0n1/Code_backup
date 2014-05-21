# include <iostream>

using namespace std;

int main()
{
	int length = 0;
	char* arrPnt;
	cout << "how long is your word yo? :" << endl;
	cin >> length;
	arrPnt = new char[length];
	cout << "Please enter word: ";
	for (int l = 0; l < length; l++)
	{	cin >> arrPnt[l];
	}


	for(int x = 0; x < length; x++)
	{
		cout << arrPnt[x];
	}
	cout << endl;


	cout << "What letter would u like to look for?" << endl;
	char* p1 = arrPnt;
	char look;
	int howfar = 0;
	cin >> look;
	while(p1 < p1+length && *p1 != look)
	{
		howfar++;
		p1++;
	}
	cout << "The letter " << look << " was found at position " << howfar << endl;


	char* frontP = arrPnt;
	char* backP = arrPnt + length -1;
	bool palindrome = true;
	while (frontP <= backP && palindrome == true)
	{
		if ( *frontP != *backP)
			palindrome = false;
		frontP ++;
		backP--;
	}
	if(palindrome == true)
	{
		cout << "this is a palindrome!" << endl;
	}
	else
		cout << "this is NOT a palindrome =(..." << endl;


	cout << "this word in pig lattin is: ";

	char* p4 = arrPnt;
	char* p5 = arrPnt;
	char* piglattin = new char[length+3];
	char* pigpnt = piglattin;
	int position = 0;
	for(int y = 0; y < length; y++)
	{
		//if ( *p4 == 'a' || *p4 == 'e' || *p4 == 'i' || *p4 == 'o' || *p4 == 'u' || *p4 == 'y')
		//{
		//	position+10;
		//	p4--;
		//}
		if(*p4 == 'o')
		{
			position + 10;
		}
		p4++;
	}
	p4++;
	cout << endl;
	cout << position;
	cout << endl;
	while (p4 < arrPnt + length - 1)
	{
		*pigpnt = *p4;
		p4 ++;
		pigpnt ++;
	}
	while (p5 < arrPnt+length)
	{
		*pigpnt = *p5;
		p5++;
		pigpnt ++;
	}
	*pigpnt = 'a';
	pigpnt++;
	*pigpnt = 'y';
	for ( int r = 0; r <= length; r++)
	{
		cout << *piglattin;
		piglattin++;
	}
	cout << endl;
	

	system("PAUSE");
}

