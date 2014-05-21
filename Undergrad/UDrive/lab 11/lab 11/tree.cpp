#include "tree.h"

Tree::Tree(TNode *r)
{
	root = r;
}

Tree::~Tree()
{
	if( root != NULL)
		delete root;
}

void Tree::insert(int x)
{
	if(root == NULL)
		root = new TNode(x);
	else
		root->insert(x);

}

void Tree::print()
{
	if( root != NULL)
		root->print();
}

void Tree::printLeaves()
{
	if (root != NULL)
		root->printLeaves();
}

void Tree::addLayer()
{
	if(root!=NULL)
		root->addLayer();
	else
		root = new TNode( rand()%100 );

}
