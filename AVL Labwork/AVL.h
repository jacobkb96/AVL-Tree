#pragma once

#include "NodeInterface.h"
#include "AVLInterface.h"
#include "Node.h"
#include <iostream>

using namespace std;

//Have added functions that do things that needed to be done many times, rotating, balancing, etc. Also helper functions for the add, remove, and clear functions.

class AVL : public AVLInterface {
private:
	Node* root;
	
	bool grew;
	bool changed;

	bool addRoot(Node*& root, int data);
	bool removeRoot(Node*& root, int data);
	
	void rotateRight(Node*& root);
	void rotateLeft(Node*& root);
	void rebalance(Node*& root);

public:
	AVL();
	~AVL();

	Node* getRootNode() const;

	bool add(int data);

	bool remove(int data);

	void clearRoot(Node* root);
	void clear();

};