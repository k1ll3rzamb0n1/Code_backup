#ifndef WORD_H
#define WORD_H

#include <string>
using namespace std;

class Word
{
private:
	string data;
	Word* next;
public:
	Word();
	Word(string item, Word* n = NULL);
	string getData();
	Word* getNext();
	void setData(string item);
	void setNext(Word* n);
};

#endif