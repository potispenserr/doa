#pragma once
#include <iostream>
struct NodeY {
	int key;
	NodeY* left;
	NodeY* right;
	int height;

};


class DoubleAVL {
public:
	NodeY* root;

	DoubleAVL() {
		root = nullptr;
	}

	int height(NodeY* n);

	int max(int a, int b);


	NodeY* newNode(int key);


	NodeY* rightRotate(NodeY* y);

	
	NodeY* leftRotate(NodeY* x);

	int getBalance(NodeY* N);

	void insertToRoot(int key);

	NodeY* insert(NodeY* node, int key);

	NodeY* minValueNode(NodeY* node);

	NodeY* deleteNode(NodeY* root, int key);

	void preOrder(NodeY* root);

};
