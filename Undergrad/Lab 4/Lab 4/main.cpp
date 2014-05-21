/****************************************************************
 * File: main.cpp
 * Description: The application file for Lab 4.
 ***************************************************************/

#include <iostream>
#include "rectangle.h"
#include "triangle.h"
using namespace std;

int main()
{
	
Shape*** grid = new Shape**[4];
for (int i = 0; i < 4; i++)
{
	grid[i]= new Shape*[4];
}
for(int row = 0; row < 4; row++)
{
	for(int col = 0; col < 4; col++)
	{
		if (row <2)
		{
			grid[row][col] = new Rectangle(3,3,3,3);
		}
		else
			grid[row][col] = new Triangle(3,3,3);
	}
}

int a;
int b;
int c,e,f;
int d;

cout << "coordinate: a: ";
cin >>a;
cout << "coordinate: b: ";
cin >>b;

cout << "coordinate: c: ";
cin >>c;
cout << "coordinate: d: ";
cin >>d;

cout << "coordinate: e: ";
cin >>e;
cout << "coordinate: f: ";
cin >>f;

grid[a][b]->draw();
cout << endl;

system("PAUSE");

grid[c][d]->draw();

system("PAUSE");

grid[e][f]->draw();

system("PAUSE");





}