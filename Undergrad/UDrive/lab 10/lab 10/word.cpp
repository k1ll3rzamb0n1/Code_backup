#include "Word.h"
using namespace std;

Word::Word()
{
	next = NULL;
}
Word::Word(string item, int p, Word* n)
{
	data = item;
	next = n;
	pr = p;
}
string Word::getData()
{
	return data;
}
Word* Word::getNext()
{
	return next;
}
int Word::getPr()
{
	return pr;
}
void Word::setPr(int p)
{
	pr = p;
}
void Word::setData(string item)
{
	data = item;
}
void Word::setNext(Word* n)
{
	next = n;
}
