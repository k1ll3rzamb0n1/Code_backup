#include "tnode.h"

TNode::TNode(int d, TNode* l, TNode* r)
{
	data = d;
	lchild = l;
	rchild = r;
}

void TNode::insert(int x)
{
	if(x < data)
		{
			if(lchild == NULL)
				lchild = new TNode(x);
			else
				lchild->insert(x);
		}
	else
		{
			if(rchild == NULL)
				rchild = new TNode(x);
			else
				rchild->insert(x);
		}

}

void TNode::print()
{
	
		cout << data << endl;

		if(lchild != NULL)
		{
			lchild->print();
		}

		if(rchild != NULL)
		{
			rchild->print();
		}
}

void TNode::printLeaves()
{
	if(lchild == NULL && rchild == NULL)
	{
		cout << data << endl;
	}
	if(lchild != NULL)
	{
		lchild->printLeaves(); 
	}
	if(rchild != NULL)
	{
		rchild->printLeaves();
	}
}

void TNode::addLayer()
{
	if(lchild!= NULL)
	{
		lchild->addLayer();
	}
	if(rchild != NULL)
	{
		rchild->addLayer();
	}
	if(lchild == NULL && rchild == NULL)
	{
		lchild = new TNode( rand() % data );
		rchild = new TNode(data);
	}
}