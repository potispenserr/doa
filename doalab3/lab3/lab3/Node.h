#pragma once
#include "DoubleAVL.h"
struct Node
{
	int key;
	Node* left;
	Node* right;
	DoubleAVL* treeY = new DoubleAVL();

	int height;
};
