#pragma once
#include "NodeInterface.h"
#include <iostream>
using namespace std;

class Node : public NodeInterface{

private:
	int height;
	int balance;
	int data;

public:
	Node(const int& data, Node* left = NULL, Node* right = NULL, const int& balance = 0, const int& height = 0);
	~Node() {}

	int getData() const;

	Node* getLeftChild() const;

	Node* getRightChild() const;

	/*
	* Returns the height of this node. The height is the number of nodes
	* along the longest path from this node to a leaf.  While a conventional
	* interface only gives information on the functionality of a class and does
	* not comment on how a class should be implemented, this function has been
	* provided to point you in the right direction for your solution.  For an
	* example on height, see page 448 of the text book.
	*
	* @return the height of this tree with this node as the local root.
	*/
	int getHeight();

	int getBalance();

	void setData(int data);
	void BalanceUp();
	void BalanceDown();
	void HeightUp();
	void HeightDown();
	int refreshTree();

	Node* left;
	Node* right;

	
};
