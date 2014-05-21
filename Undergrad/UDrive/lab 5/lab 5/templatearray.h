
#include <iostream>
#include <string>
using namespace std;

#ifndef TEMPLATEARRAY_H
#define TEMPLATEARRAY_H

template<class T>
class Templatearray
{
private:
	T ar[10];
	int used;
public:
	Templatearray();
	void print();
	void addElement(T e);
	void removeElement(int u);
	T largest();
};

#endif

template <class T>
Templatearray<T>::Templatearray()
{
	used = 0;
}

template <class T>
void Templatearray<T>::print()
{
	for ( int i = 0; i < used; i++)
	{

		cout << ar[i];
	}
}

template <class T>
void Templatearray<T>::addElement(T e)
{
	if (used < 10)
	{
		ar[used] = e;
		used++;
	}
}


template <class T>
void Templatearray<T>::removeElement(int u)
{
	for(int i = u; i < 10; i++)
	{
		ar[i] = ar[i+1];
	}
	used--;
}


template <class T>
T Templatearray<T>::largest()
{
	T large = 0;
	for(int i = 0; i < 10; i++)
	{
		if (large < ar[i])
		{
			large = ar[i];
		}
	}
	return large;
}