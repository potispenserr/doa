#include "AVL.h"

	int AVL::height(Node* n)
	{
		if (n == NULL) {

			return 0;
		}
		return n->height;
	}

	int  AVL::max(int a, int b)
	{
		return (a > b) ? a : b;
	}

	//adds a new node to both the first and second avl tree
	Node* AVL::newNode(int key, int y)
	{
		Node* node = new Node();
		node->key = key;
		node->left = NULL;
		node->right = NULL;
		node->treeY->insertToRoot(y);
		node->height = 1; 
		return(node);
	}

	Node* AVL::rightRotate(Node* y)
	{
		Node* x = y->left;
		Node* T2 = x->right;

		x->right = y;
		y->left = T2;

		y->height = max(height(y->left), height(y->right)) + 1;

		x->height = max(height(x->left), height(x->right)) + 1;

		return x;
	}

	Node* AVL::leftRotate(Node* x)
	{
		Node* y = x->right;
		Node* T4 = y->left;

		y->left = x;
		x->right = T4;

		x->height = max(height(x->left),height(x->right)) + 1;

		y->height = max(height(y->left),height(y->right)) + 1;

		return y;
	}

	int AVL::getBalance(Node* N)
	{
		if (N == NULL) {

			return 0;
		}
		return height(N->left) - height(N->right);
	}

	void AVL::insertToRoot(int key, int y) {
		root = insert(root, key, y);
	}

	void AVL::deleteFromRoot(int key, int y) {
		root = deleteNode(root, key, y);
	}


	Node* AVL::insert(Node* node, int key, int y)
	{
		if (node == NULL) {

			return(newNode(key, y));
		}

		if (key < node->key) {

			node->left = insert(node->left, key, y);
		}
		else if (key > node->key) {

			node->right = insert(node->right, key, y);
		}
		else {

			return node;
		}

		
		node->height = 1 + max(height(node->left),height(node->right));

		
		int balance = getBalance(node);

		

		
		if (balance > 1 && key < node->left->key) {

			return rightRotate(node);
		}

		
		if (balance < -1 && key > node->right->key) {

			return leftRotate(node);
		}

		
		if (balance > 1 && key > node->left->key)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		
		if (balance < -1 && key < node->right->key)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		
		return node;
	}

	
	Node* AVL::minValueNode(Node* node)
	{
		Node* current = node;

		
		while (current->left != NULL) {

			current = current->left;
		}

		return current;
	}

	// deletes node from first avl tree and nodes from second avl tree
	Node* AVL::deleteNode(Node* root, int key, int y)
	{

		
		if (root == NULL) {

			return root;
		}


		if (key < root->key) {

			root->left = deleteNode(root->left, key, y);
		}

		
		else if (key > root->key) {

			root->right = deleteNode(root->right, key, y);
		}

		
		else
		{
			
			if ((root->left == NULL) || (root->right == NULL))
			{
				Node* temp = root->left ? root->left : root->right;

				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}

				else {

					*root = *temp; 
				}
				temp->treeY->deleteNode(root->treeY->root, y);
				free(temp);
			}
			else
			{
				
				Node* temp = minValueNode(root->right);

				
				root->key = temp->key;

				
				root->right = deleteNode(root->right,
					temp->key, y);
			}
		}

		
		if (root == NULL) {

			return root;
		}

		
		root->height = 1 + max(height(root->left),
			height(root->right));

		
		int balance = getBalance(root);

		

		
		if (balance > 1 && getBalance(root->left) >= 0) {

			return rightRotate(root);
		}

		
		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		
		if (balance < -1 && getBalance(root->right) <= 0) {

			return leftRotate(root);
		}

		
		if (balance < -1 &&
			getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}

	//prints out all x values and their assosiated y values
	void  AVL::preOrder(Node* root)
	{
		if (root != NULL)
		{
			std::cout << "X: " << root->key << " " << "\n";
			std::cout << "Y: ";
			root->treeY->preOrder(root->treeY->root);
			std::cout << "\n";
			std::cout << "-------------------------------" << "\n";
			preOrder(root->left);
			preOrder(root->right);
		}
	}
