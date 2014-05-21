#ifndef TNODE_H
#define TNODE_H

#include <iostream>
using namespace std;

class TNode
{
protected:
	int data;
	TNode *lchild, *rchild;
public:
	TNode(int d = -1, TNode* l = NULL, TNode* r = NULL);

	void insert(int x);
	void print();
	void printLeaves();
	void addLayer();
};

#endif