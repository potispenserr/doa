#include "DoubleAVL.h"

int DoubleAVL::height(NodeY* n) {

	if (n == nullptr)
		return 0;
	return n->height;
}


int DoubleAVL::max(int a, int b)
{
	return (a > b) ? a : b;
}

NodeY* DoubleAVL::newNode(int key)
{
	NodeY* node = new NodeY();
	node->key = key;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1; // the new node is added at leaf
	return(node);
}

// rotates the tree with root of y to the right
NodeY* DoubleAVL::rightRotate(NodeY* y)
{
	NodeY* x = y->left;
	NodeY* T2 = x->right;

	x->right = y;
	y->left = T2;

	// updates the height 
	y->height = max(height(y->left), height(y->right)) + 1;

	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

// rotates the tree with root of x to the right
NodeY* DoubleAVL::leftRotate(NodeY* x)
{
	NodeY* y = x->right;
	NodeY* T4 = y->left;

	y->left = x;
	x->right = T4;

	// updates the height 
	x->height = max(height(x->left), height(x->right)) + 1;

	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

// gets balance of node n
int DoubleAVL::getBalance(NodeY* N)
{
	if (N == nullptr) {

		return 0;
	}
	return height(N->left) - height(N->right);
}

// wrapper function for insert
void DoubleAVL::insertToRoot(int key) {

	root = insert(root, key);
}

// inserts the key into the tree and maybe rotates the tree a couple of times
NodeY* DoubleAVL::insert(NodeY* node, int key)
{
	if (node == nullptr) {
		return(newNode(key));
	}
	if (key < node->key) {

		node->left = insert(node->left, key);
	}
	else if (key > node->key) {

		node->right = insert(node->right, key);
	}
	else {  // no duplicates >:(
		return node;
	}

	// updates the height of ancestor node
	node->height = 1 + max(height(node->left),height(node->right));

	int balance = getBalance(node);


	// left left
	if (balance > 1 && key < node->left->key) {
		return rightRotate(node);
	}

	// right right
	if (balance < -1 && key > node->right->key) {
		return leftRotate(node);
	}

	// left right
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// right left
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

// gets min value of tree/subtree node
NodeY* DoubleAVL::minValueNode(NodeY* node)
{
	NodeY* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != nullptr) {
		current = current->left;
	}
			
	return current;
}

//deletes node with specified key and maybe rotates the tree
NodeY* DoubleAVL::deleteNode(NodeY* root, int key)
{
	if (root == nullptr) {
		return root;
	}
		

	//if key is smaller than root do deleteNode on left side
	if (key < root->key)
		root->left = deleteNode(root->left, key);

	//if key is mightier than root do deleteNode on right side
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	// else if the key is the same as root
	else
	{
		// node with only one or no child 
		if ((root->left == NULL) || (root->right == NULL))
		{
			NodeY* temp = root->left ?
				root->left :
				root->right;

			// if no child 
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else 
				*root = *temp; 
			delete(temp);
		}
		else
		{
			// get smallest in right subtree as successor
			NodeY* temp = minValueNode(root->right);

			root->key = temp->key;

			root->right = deleteNode(root->right, temp->key);
		}
	}


	if (root == nullptr) {
		return root;
	}
			
	// update height
	root->height = 1 + max(height(root->left), height(root->right));

		
	int balance = getBalance(root);


	// left left
	if (balance > 1 && getBalance(root->left) >= 0) {
		return rightRotate(root);
	}
			

	// left right 
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// right right 
	if (balance < -1 && getBalance(root->right) <= 0) {
		return leftRotate(root);
	}
			

	// right left
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

//prints out the tree in preorder
void DoubleAVL::preOrder(NodeY* root)
{
	if (root != nullptr)
	{
		std::cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}