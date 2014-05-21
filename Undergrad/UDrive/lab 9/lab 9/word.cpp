#include "Word.h"
using namespace std;

Word::Word()
{
	next = NULL;
}
Word::Word(string item, Word* n)
{
	data = item;
	next = n;
}
string Word::getData()
{
	return data;
}
Word* Word::getNext()
{
	return next;
}
void Word::setData(string item)
{
	data = item;
}
void Word::setNext(Word* n)
{
	next = n;
}
