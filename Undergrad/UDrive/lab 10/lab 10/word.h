#ifndef WORD_H
#define WORD_H

#include <string>
using namespace std;

class Word
{
private:
	string data;
	int pr;
	Word* next;
public:
	Word();
	Word(string item, int p, Word* n = NULL);

	string getData();
	Word* getNext();
	int getPr();

	void setData(string item);
	void setNext(Word* n);
	void setPr(int p);
};

#endif