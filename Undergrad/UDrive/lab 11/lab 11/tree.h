#ifndef TREE_H
#define TREE_H

#include "tnode.h"

class Tree
{
protected:
	TNode* root;
public:
	Tree(TNode* r = NULL);
	~Tree();

	void insert(int x);
	void print();
	void printLeaves();
	void addLayer();

	
};

#endif 