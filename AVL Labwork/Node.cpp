#include "Node.h"

Node::Node(const int& data, Node *left, Node *right,const int& balance, const int& height){
	this->data = data;
	this->left = left;
	this->right = right;
	this->balance = balance;
	this->height = height;

}

int Node::getData() const
{
    return data;
}

Node* Node::getLeftChild() const
{
    return left;
}

Node* Node::getRightChild() const
{
    return right;
}

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
int Node::getHeight()
{
    return height;
}

int Node::getBalance(){
	return balance; 
}

void Node::setData(int data){
	this -> data = data;
}

void Node::BalanceUp(){
	this->balance = balance+1;
}

void Node::BalanceDown(){
	this->balance = balance-1;
}

void Node::HeightUp(){
	this->height = height+1;
}

void Node::HeightDown(){
	this->height = height-1;
}

//This little thing just 'refreshes' all the info about the current tree. Makes sure balance and height trackers are accurate so everything works in the rebalance function.
int Node::refreshTree(){
	if (right == NULL && left==NULL){
		balance = 0;
		height = 1;
	}
	else if (right == NULL){
		height = left->refreshTree() + 1;
		balance = 0 - left->getHeight();
	}
	else if (left == NULL){
		height = right->refreshTree() + 1;
		balance = right->getHeight();
	}
	else{
		height = max(left->refreshTree(), right->refreshTree()) + 1;
		balance = right->getHeight() - left->getHeight();
	}
	return height;
}