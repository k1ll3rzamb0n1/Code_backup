/**************************************************************************************
 *  File: CharArray.cpp
 *  Description: Implementation file for a simple string class containing two sorting
 *               algorithms to sort the letters in the string from smallest to largest.
 *************************************************************************************/

#include <iostream>
#include "CharArray.h"

/*****  Constructors *****/
CharArray::CharArray()
{
	size = 0;
}

CharArray::CharArray(string s) // converts from regular to our type of strings
{
	size = s.length();
	arr = new char[size];
	for (int i = 0; i < size; i++)
		arr[i] = s.at(i);
}

/*****  Accessors  *****/
int CharArray::getSize()
{
	return size;
}

char& CharArray::operator [] (int index)
{
	if (index >= 0 && index < size)
		return arr[index];
	cout << "Bad index!";
	system("PAUSE");
	exit(0);
}

/*****  Print Functions  *****/
void CharArray::print(int start, int end)  // prints substring from start to end, inclusive
{
	if (start >= 0 && start < size && end >= 0 && end < size)
		if (start <= end)
			for (int i = start; i <= end; i++)
				cout << arr[i];
		else
			cout << "Error: start larger than stop.\n";
	else
		cout << "Error: invalid indexes.\n";
}

void CharArray::print()  // prints whole array
{
	print(0, size-1);
}

ostream& operator << (ostream& out, CharArray c)  // alternative way to print full array
{
	for (int i = 0; i < c.getSize(); i++)
			cout << c[i];
	return out;
}

/*****  Sorting Algorithms  *****/

void CharArray::selectionSort()
{

	for(int front = 0; front < size-1; front ++)
		 {
		   int smallest = front;
		   for(int cur = front +1; cur < size; cur ++)
			{ 
			   if(arr[smallest]> arr[cur])
				{
				  smallest = cur;
				}
			}
		   char temp = arr[front];
		   arr[front] = arr[smallest];
		   arr[smallest] = temp;
		 }

}

void CharArray::bubbleSort()
{
	// To Do: Please implement me!
	cout << "Insertion Sort still needs to be implemented.\n";
}

void CharArray::mergeSort(int start, int end)
{
	// To Do: Please implement me!
	cout << "Merge Sort still needs to be implemented.\n";
}

void CharArray::merge(int start, int mid, int end)
{
	// To Do: Please implement me!
	cout << "The merging subalgorithm of merge sort still needs to be implemented.\n";
}

void CharArray::quickSort(int start, int end)
{
	if (end <= start)
		return;
	int p = partition(start,end);
	print();
	cout << endl;
	quickSort(start,p);
	quickSort(p+1,end);
}

int CharArray::partition(int first, int last)
{
	char pivot = arr[first];
	while(first < last)
	{
		while(arr[first] < pivot && first <= last)
		{
			first++;
		}
		while(arr[last] > pivot && first <= last)
		{
			last--;
		}

		char temp = arr[first];
		arr[first] = arr[last];
		arr[last] = temp;
		
	}

	return last;
}