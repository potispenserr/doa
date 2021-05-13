#pragma once
#include "Node.h"

class AVL {
public:
	Node* root;

	AVL() {
		root = nullptr;
	}
	
	int height(Node* n);

	int max(int a, int b);


	Node* newNode(int key, int y);

	
	Node* rightRotate(Node* y);

	
	Node* leftRotate(Node* x);

	
	int getBalance(Node* N);

	void insertToRoot(int key, int y);

	void deleteFromRoot(int key, int y);

	
	Node* insert(Node* node, int key, int y);

	Node* minValueNode(Node* node);

	
	Node* deleteNode(Node* root, int key, int y);

	void preOrder(Node* root);

};