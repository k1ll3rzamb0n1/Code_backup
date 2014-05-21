/**************************************************************************************
 *  File: CharArray.h
 *  Description: Header file for a simple string class containing two sorting
 *               algorithms to sort the letters in the string from smallest to largest.
 *************************************************************************************/

#ifndef CHARARRAY_H
#define CHARARRAY_H

#include <string>  // to allow conversion from standard strings to our strings
using namespace std;

class CharArray
{
private:
	char* arr;  // points to the dynamically allocated array
	int size;
public:
	CharArray();
	CharArray(string s);
	int getSize();
	void print(int start, int end);  // print substring
	void print();  // print full string
	char& operator [] (int index);  // allow access to characters in string

	// Sorting algorithms for you to implement: pick 2 of the 4
	void selectionSort();
	void bubbleSort();
	void mergeSort(int start, int end);
	void merge(int start, int mid, int end);
	void quickSort(int start, int end);
	int partition(int first, int last);
};

ostream& operator << (ostream& out, CharArray c);  // alternative way to print full string

#endif